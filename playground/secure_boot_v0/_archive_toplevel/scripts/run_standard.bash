#!/usr/bin/env bash
# run_v0.bash — build the secure_boot_v0 software and run the Verilator sim.
#
# Prereq: run ./setup.bash once first (it writes .env.local).
#
# Pipeline:
#   sw/         -> generate signing key, sign+pack ROM_EXT+BL0 -> d_sram.hex + trusted_pubkey.h
#   (sync key)  -> copy the freshly-generated pubkey into the ROM's source tree
#   test_sw/    -> build the boot ROM image (rom.imem.hex) and overlay the signed
#                  image into the combined DMEM init (rom_with_image.dmem.hex)
#   rtl/top.sv  -> point IMEM_INIT_HEX / DMEM_INIT_HEX at the images on THIS machine
#   fusesoc     -> build + run the Verilator model -> sim.log
#
# Usage:
#   ./run_v0.bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ENV_FILE="$SCRIPT_DIR/.env.local"

say()  { printf '\033[1;34m[run]\033[0m %s\n' "$*"; }
ok()   { printf '\033[1;32m[ ok ]\033[0m %s\n' "$*"; }
die()  { printf '\033[1;31m[fail]\033[0m %s\n' "$*" >&2; exit 1; }

[[ -f "$ENV_FILE" ]] || die "Missing $ENV_FILE — run ./setup.bash first."
# shellcheck disable=SC1090
source "$ENV_FILE"

# Activate the toolchain + FuseSoC venv for this process.
export PATH="$RISCV_BIN:$PATH"
# shellcheck disable=SC1091
source "$FUSESOC_VENV/bin/activate"

command -v "${RISCV_PREFIX}gcc" >/dev/null 2>&1 || die "${RISCV_PREFIX}gcc not on PATH (re-run setup.bash)."
command -v fusesoc            >/dev/null 2>&1 || die "fusesoc not on PATH (re-run setup.bash)."

cd "$SCRIPT_DIR"

# ---------------------------------------------------------------------------
# 1) Build + sign the boot images -> sw/build/d_sram.hex, sw/boot/trusted_pubkey.h
# ---------------------------------------------------------------------------
say "Building + signing boot images (sw/) with ${RISCV_PREFIX}* ..."
make -C sw clean >/dev/null 2>&1 || true
make -C sw all RISCV_PREFIX="$RISCV_PREFIX"
[[ -f sw/build/d_sram.hex ]] || die "sw build did not produce build/d_sram.hex"
ok "Signed image: sw/build/d_sram.hex"

# ---------------------------------------------------------------------------
# 2) Sync the trusted public key into the ROM source so the ROM verifies the
#    key that actually signed the image (matters if ROM verification is enabled).
# ---------------------------------------------------------------------------
cp sw/boot/trusted_pubkey.h test_sw/c/utils/trusted_pubkey.h
ok "Synced trusted_pubkey.h into the ROM source tree"

# ---------------------------------------------------------------------------
# 3) Build the ROM image + overlay the signed image into the DMEM init hex
# ---------------------------------------------------------------------------
say "Building boot ROM image (test_sw/) ..."
make -C test_sw clean >/dev/null 2>&1 || true
make -C test_sw rom RISCV_PREFIX="$RISCV_PREFIX"
IMEM_HEX="$SCRIPT_DIR/test_sw/hex/rom.imem.hex"
DMEM_HEX="$SCRIPT_DIR/test_sw/hex/rom_with_image.dmem.hex"
[[ -f "$IMEM_HEX" && -f "$DMEM_HEX" ]] || die "ROM hex images were not produced"
ok "IMEM: $IMEM_HEX"
ok "DMEM: $DMEM_HEX"

# ---------------------------------------------------------------------------
# 4) Point the RTL at the images on THIS machine (Verilator $readmemh needs an
#    absolute path; this rewrite is idempotent and only touches the active
#    parameter lines, not the commented-out alternatives).
# ---------------------------------------------------------------------------
TOP_SV="$SCRIPT_DIR/rtl/top.sv"
sed -i -E "/^[[:space:]]*parameter string IMEM_INIT_HEX/ s|\"[^\"]*\"|\"$IMEM_HEX\"|" "$TOP_SV"
sed -i -E "/^[[:space:]]*parameter string DMEM_INIT_HEX/ s|\"[^\"]*\"|\"$DMEM_HEX\"|" "$TOP_SV"
ok "Set IMEM_INIT_HEX / DMEM_INIT_HEX in rtl/top.sv"

# ---------------------------------------------------------------------------
# 5) Build + run the Verilator simulation
# ---------------------------------------------------------------------------
say "Building + running Verilator sim (this takes a few minutes; log -> sim.log) ..."
fusesoc --cores-root ../.. run --target=sim --tool=verilator \
        xinting:playground:top_standard > sim.log 2>&1 \
  && ok "Simulation finished" \
  || die "Simulation failed — see sim.log (tail below):
$(tail -n 20 sim.log)"

# ---------------------------------------------------------------------------
# 6) Report the UART console output (what the boot chain printed)
# ---------------------------------------------------------------------------
echo
say "===== Simulation output (top_macro / tb_top.sv, raw log tail) ====="
tail -n 40 sim.log

echo
say "Artifacts:"
echo "  sim.log         : full simulation log (RVFI trace, TL-UL + UART activity)"
echo "  *.fst           : run 'make copy' to lift the waveform into this dir"
echo "  esram_dump.hex  : exec-SRAM contents dumped at end of sim (in the build dir)"
ok "Done."
