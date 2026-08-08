#!/usr/bin/env bash
# run_gls.bash — gate-level simulation (GLS) of the taped-out top_pd netlist.
#
# This is the check that was missing: run_v1.bash/run_standard.bash/run_macro.bash
# only ever simulate RTL (`top` / `top_macro`); top_pd.core is lint-only
# (blackbox stubs, never simulated). This script builds the SAME test_sw boot
# image those scripts use, then simulates the actual post-PnR gate netlist
# (top_pd.nl.v + the 4 hardened macro netlists) and checks it produces the
# same UART boot trace.
#
# Does not modify any existing file: sw/, test_sw/, rtl/, secure_boot_v0.core,
# top_pd.core are all only *read* or *invoked*, never edited. New files live
# under gls/.
#
# Prereq: run ./setup.bash once first (it writes .env.local) -- same prereq
# run_v1.bash has.
#
# Usage:
#   ./run_gls.bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ENV_FILE="$SCRIPT_DIR/.env.local"
GLS_DIR="$SCRIPT_DIR/gls"

say()  { printf '\033[1;34m[gls]\033[0m %s\n' "$*"; }
ok()   { printf '\033[1;32m[ ok ]\033[0m %s\n' "$*"; }
die()  { printf '\033[1;31m[fail]\033[0m %s\n' "$*" >&2; exit 1; }

[[ -f "$ENV_FILE" ]] || die "Missing $ENV_FILE — run ./setup.bash first."
# shellcheck disable=SC1090
source "$ENV_FILE"

export PATH="$RISCV_BIN:$PATH"
# shellcheck disable=SC1091
source "$FUSESOC_VENV/bin/activate"

command -v "${RISCV_PREFIX}gcc" >/dev/null 2>&1 || die "${RISCV_PREFIX}gcc not on PATH (re-run setup.bash)."
command -v fusesoc            >/dev/null 2>&1 || die "fusesoc not on PATH (re-run setup.bash)."

cd "$SCRIPT_DIR"

# ---------------------------------------------------------------------------
# 1) Build + sign the boot images -> sw/build/d_sram.hex, sw/boot/trusted_pubkey.h
#    (identical step to run_v1.bash — reusing the existing sw/ Makefile as-is)
# ---------------------------------------------------------------------------
say "Building + signing boot images (sw/) with ${RISCV_PREFIX}* ..."
make -C sw clean >/dev/null 2>&1 || true
make -C sw all RISCV_PREFIX="$RISCV_PREFIX"
[[ -f sw/build/d_sram.hex ]] || die "sw build did not produce build/d_sram.hex"
cp sw/boot/trusted_pubkey.h test_sw/c/utils/trusted_pubkey.h
ok "Signed image + trusted_pubkey.h synced"

# ---------------------------------------------------------------------------
# 2) Build the ROM image + overlay the signed image into the DMEM init hex
#    (identical step to run_v1.bash — reusing the existing test_sw/ Makefile)
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
# 3) Build the GLS simulation binary (netlists + PDK cell models + new TB)
#    Unlike run_v1.bash, nothing here needs $readmemh baked into RTL via sed
#    -- gls_sram_preload.sv backdoor-loads the two hex images via plusargs at
#    run time, so the same build works for any boot image.
# ---------------------------------------------------------------------------
say "Building GLS model (this parses two multi-MB gate netlists; can take a while) -> gls_build.log ..."
fusesoc --cores-root ../.. run --target=sim_gls --tool=verilator --build \
        xinting:playground:secure_boot_v0_gls > gls_build.log 2>&1 \
  && ok "GLS build finished" \
  || die "GLS build failed — see gls_build.log (tail below):
$(tail -n 40 gls_build.log)"

BUILD_DIR="$SCRIPT_DIR/build/xinting_playground_secure_boot_v0_gls_0.1/sim_gls-verilator"
BIN="$BUILD_DIR/Vtop_pd_gls_tb"
[[ -x "$BIN" ]] || die "Expected GLS binary not found at $BIN — check gls_build.log"

# ---------------------------------------------------------------------------
# 4) Run the GLS binary directly (bypassing fusesoc's own run step so we can
#    hand it fresh +gls_imem_hex=/+gls_dmem_hex= plusargs without rebuilding).
# ---------------------------------------------------------------------------
say "Running GLS simulation -> gls_sim.log ..."
( cd "$BUILD_DIR" && ./Vtop_pd_gls_tb "+gls_imem_hex=$IMEM_HEX" "+gls_dmem_hex=$DMEM_HEX" ) \
  > gls_sim.log 2>&1 \
  && ok "GLS simulation finished" \
  || die "GLS simulation failed — see gls_sim.log (tail below):
$(tail -n 40 gls_sim.log)"

echo
say "===== GLS simulation output (raw log tail) ====="
tail -n 40 gls_sim.log
echo "===== UART output (hardware-decoded serial bytes, taped-out netlist) ====="
if grep -q "UART_RX" gls_sim.log; then
   grep "UART_RX" gls_sim.log | sed 's/^/  /'
   STREAM="$(grep -oE "byte=0x[0-9a-f]+ \('.'\)" gls_sim.log | sed -E "s/.*\('(.)'\)/\1/" | tr -d '\n')"
   echo
   printf '  decoded stream: \033[1;36m%s\033[0m\n' "$STREAM"
   echo
   echo "  Compare against the RTL sim trace from run_v1.bash — expected 'sJPEXTJPB'"
   echo "  (ROM -> ROM_EXT -> BL0). A match means the actual taped-out netlist boots"
   echo "  the same firmware the same way the RTL said it would."
   echo
else
   echo "  (no UART bytes decoded — check gls_sim.log; the SRAM preload messages"
   echo "   from gls_sram_preload.sv, printed near the top of the log, are the"
   echo "   first thing to check if nothing boots)"
fi

echo
say "Artifacts (in $BUILD_DIR):"
echo "  gls_build.log, gls_sim.log : build/run logs"
echo "  secure_boot_v0_gls.fst     : waveform (open with gtkwave)"
ok "Done."
