#!/usr/bin/env bash
# run_macro.bash — build the secure boot software and run Verilator sim 
# using Tim's OCD SRAM macro top module (top_macro.sv) and tb_top.sv.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ENV_FILE="$SCRIPT_DIR/.env.local"

say()  { printf '\033[1;34m[run]\033[0m %s\n' "$*"; }
ok()   { printf '\033[1;32m[ ok ]\033[0m %s\n' "$*"; }
die()  { printf '\033[1;31m[fail]\033[0m %s\n' "$*" >&2; exit 1; }

[[ -f "$ENV_FILE" ]] || die "Missing $ENV_FILE — run ./setup.bash first."
source "$ENV_FILE"

export PATH="$RISCV_BIN:$PATH"
source "$FUSESOC_VENV/bin/activate"

cd "$SCRIPT_DIR"

# 1) Build + sign boot images
say "Building + signing boot images (sw/) ..."
make -C sw clean >/dev/null 2>&1 || true
make -C sw all RISCV_PREFIX="$RISCV_PREFIX"
[[ -f sw/build/d_sram.hex ]] || die "sw build did not produce build/d_sram.hex"
ok "Signed image: sw/build/d_sram.hex"

# 2) Sync trusted public key
cp sw/boot/trusted_pubkey.h test_sw/c/utils/trusted_pubkey.h
ok "Synced trusted_pubkey.h into ROM source tree"

# 3) Build ROM image + overlay DMEM
say "Building boot ROM image (test_sw/) ..."
make -C test_sw clean >/dev/null 2>&1 || true
make -C test_sw rom RISCV_PREFIX="$RISCV_PREFIX"
IMEM_HEX="$SCRIPT_DIR/test_sw/hex/rom.imem.hex"
DMEM_HEX="$SCRIPT_DIR/test_sw/hex/rom_with_image.dmem.hex"
[[ -f "$IMEM_HEX" && -f "$DMEM_HEX" ]] || die "ROM hex images were not produced"

# 4) Point top_macro.sv at the absolute paths for $readmemh
TOP_MACRO_SV="$SCRIPT_DIR/rtl/top_macro.sv"
sed -i -E "/^[[:space:]]*parameter string IMEM_INIT_HEX/ s|\"[^\"]*\"|\"$IMEM_HEX\"|" "$TOP_MACRO_SV"
sed -i -E "/^[[:space:]]*parameter string DMEM_INIT_HEX/ s|\"[^\"]*\"|\"$DMEM_HEX\"|" "$TOP_MACRO_SV"
ok "Set IMEM_INIT_HEX / DMEM_INIT_HEX in rtl/top_macro.sv"

# 5) Build + run Verilator simulation using top_macro core
say "Building + running Verilator sim with Tim's SRAM macro (log -> sim_macro.log) ..."
fusesoc --cores-root ../.. run --target=sim --tool=verilator \
        xinting:playground:top_macro > sim_macro.log 2>&1 \
  && ok "Simulation finished" \
  || die "Simulation failed — see sim_macro.log (tail below):
$(tail -n 20 sim_macro.log)"

# 6) Report UART console output
echo
say "===== UART output (hardware-decoded serial bytes) ====="
if grep -q "UART_RX" sim_macro.log; then
  grep "UART_RX" sim_macro.log | sed 's/^/  /'
  STREAM="$(grep -oE "byte=0x[0-9a-f]+ \('.'\)" sim_macro.log | sed -E "s/.*\('(.)'\)/\1/" | tr -d '\n')"
  echo
  printf '  decoded stream: \033[1;36m%s\033[0m\n' "$STREAM"
  echo
  echo "  Expected full chain: 'sJPEXTJPB' (ROM -> ROM_EXT -> BL0)"
else
  echo "  (no UART bytes decoded — check sim_macro.log)"
fi
ok "Done."
