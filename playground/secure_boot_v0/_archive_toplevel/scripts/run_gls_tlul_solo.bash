#!/usr/bin/env bash
# run_gls_tlul_solo.bash — standalone GLS of just tlul_sram_if_macro.
#
# First rung of building top_pd_puf verification up one real macro at a
# time (see gls/tlul_sram_if_macro_solo_gls.core header for why). No
# firmware build, no riscv toolchain needed -- the testbench drives a
# directed TL-UL write+read sequence itself.
#
# Prereq: run ./setup.bash once first (it writes .env.local).
#
# Usage:
#   ./run_gls_tlul_solo.bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ENV_FILE="$SCRIPT_DIR/.env.local"
GLS_DIR="$SCRIPT_DIR/gls"

say()  { printf '\033[1;34m[tlul-solo]\033[0m %s\n' "$*"; }
ok()   { printf '\033[1;32m[ ok ]\033[0m %s\n' "$*"; }
die()  { printf '\033[1;31m[fail]\033[0m %s\n' "$*" >&2; exit 1; }

[[ -f "$ENV_FILE" ]] || die "Missing $ENV_FILE — run ./setup.bash first."
# shellcheck disable=SC1090
source "$ENV_FILE"

# shellcheck disable=SC1091
source "$FUSESOC_VENV/bin/activate"
command -v fusesoc >/dev/null 2>&1 || die "fusesoc not on PATH (re-run setup.bash)."

cd "$SCRIPT_DIR"

say "Building standalone tlul_sram_if_macro GLS model -> gls_tlul_solo_build.log ..."
fusesoc --cores-root ../.. run --target=sim_gls --tool=verilator --build \
        xinting:playground:tlul_sram_if_macro_solo_gls > gls_tlul_solo_build.log 2>&1 \
  && ok "Build finished" \
  || die "Build failed — see gls_tlul_solo_build.log (tail below):
$(tail -n 40 gls_tlul_solo_build.log)"

BUILD_DIR="$SCRIPT_DIR/build/xinting_playground_tlul_sram_if_macro_solo_gls_0.1/sim_gls-verilator"
BIN="$BUILD_DIR/Vtlul_sram_if_macro_solo_gls_tb"
[[ -x "$BIN" ]] || die "Expected GLS binary not found at $BIN — check gls_tlul_solo_build.log"

say "Running standalone tlul_sram_if_macro GLS -> gls_tlul_solo_sim.log ..."
( cd "$BUILD_DIR" && ./Vtlul_sram_if_macro_solo_gls_tb ) \
  > gls_tlul_solo_sim.log 2>&1 \
  || true   # let the log speak; PASS/FAIL is parsed below regardless of exit code

echo
say "===== TLUL_SOLO_GLS output ====="
grep "TLUL_SOLO_GLS" gls_tlul_solo_sim.log | sed 's/^/  /'
echo

if grep -q "\[TLUL_SOLO_GLS\] PASS" gls_tlul_solo_sim.log; then
  printf '\033[1;32mPASS\033[0m: gate-level tlul_sram_if_macro write+readback works standalone.\n'
elif grep -q "\[TLUL_SOLO_GLS\] FAIL" gls_tlul_solo_sim.log; then
  printf '\033[1;31mFAIL\033[0m: see gls_tlul_solo_sim.log for detail (per-request a_ready/d_valid cycle numbers are printed above).\n'
else
  printf '\033[1;33mCHECK\033[0m: no PASS/FAIL banner found — inspect gls_tlul_solo_sim.log directly (tail below):\n'
  tail -n 40 gls_tlul_solo_sim.log
fi
