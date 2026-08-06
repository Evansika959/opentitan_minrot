#!/usr/bin/env bash
# run_gls_puf_smoke.bash — minimal smoke test for the top_pd_puf GLS harness.
#
# Sibling of ../run_gls_smoke.bash (which does this for the older top_pd):
# the full secure-boot ROM+DMEM firmware doesn't fit top_pd_puf's real,
# size-constrained DMEM macro (256-word capacity vs ~309 words needed --
# see that discussion for the numbers). This proves the GLS mechanism and
# the taped-out netlist's actual real-macro hardware paths (IMEM fetch,
# ESRAM read/write, the PUF trigger/poll/read path) using a hand-written
# ~40-instruction program (gls/smoke_puf_boot.S) that fits in one IMEM bank
# and never touches DMEM at all.
#
# Reuses split_imem_banks.py and test_sw/bin2hex32.py as utilities
# (invoked, not edited) — same convention run_secure_boot_macro21_demo.bash
# established for the real firmware, just pointed at a tiny binary instead.
#
# Prereq: run ./setup.bash once first (writes .env.local), same as
# run_gls.bash / run_gls_smoke.bash.
#
# Usage:
#   ./run_gls_puf_smoke.bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ENV_FILE="$SCRIPT_DIR/.env.local"
GLS_DIR="$SCRIPT_DIR/gls"
SMOKE_DIR="$GLS_DIR/smoke_puf"
IMEM_HEXDIR="$SMOKE_DIR/imem_banks"
SPLIT_IMEM_BANKS="/foss/designs/sram_puf/ibex_demo/split_imem_banks.py"

say()  { printf '\033[1;34m[puf-smoke]\033[0m %s\n' "$*"; }
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
[[ -f "$SPLIT_IMEM_BANKS" ]] || die "Missing $SPLIT_IMEM_BANKS"

mkdir -p "$SMOKE_DIR" "$IMEM_HEXDIR"
cd "$SCRIPT_DIR"

# ---------------------------------------------------------------------------
# 1) Assemble the tiny program -> smoke_puf.elf -> smoke_puf.text.bin
# ---------------------------------------------------------------------------
say "Assembling gls/smoke_puf_boot.S ..."
"${RISCV_PREFIX}gcc" -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles \
  -Wl,-T,"$GLS_DIR/smoke_puf.ld" -o "$SMOKE_DIR/smoke_puf.elf" "$GLS_DIR/smoke_puf_boot.S"
"${RISCV_PREFIX}objcopy" -O binary --only-section=.text \
  "$SMOKE_DIR/smoke_puf.elf" "$SMOKE_DIR/smoke_puf.text.bin"
ok "Assembled: $SMOKE_DIR/smoke_puf.text.bin ($(stat -c%s "$SMOKE_DIR/smoke_puf.text.bin") bytes)"

# ---------------------------------------------------------------------------
# 2) Prepend the 0x80-byte reset-vector gap (Ibex always fetches its first
#    instruction from {boot_addr_i[31:8], 8'h80} -- ibex_if_stage.sv -- same
#    convention run_gls_smoke.bash uses), convert to $readmemh hex.
# ---------------------------------------------------------------------------
say "Building IMEM hex image ..."
dd if=/dev/zero bs=1 count=128 status=none of="$SMOKE_DIR/pad.bin"
cat "$SMOKE_DIR/pad.bin" "$SMOKE_DIR/smoke_puf.text.bin" > "$SMOKE_DIR/smoke_puf.imem.bin"
rm -f "$SMOKE_DIR/pad.bin"
python3 "$SCRIPT_DIR/test_sw/bin2hex32.py" "$SMOKE_DIR/smoke_puf.imem.bin" > "$SMOKE_DIR/smoke_puf.imem.hex"
WORDS=$(wc -l < "$SMOKE_DIR/smoke_puf.imem.hex")
ok "IMEM image: $SMOKE_DIR/smoke_puf.imem.hex ($WORDS words, one bank's capacity is 256)"
[[ "$WORDS" -le 256 ]] || die "Smoke program ($WORDS words) exceeds one bank's 256-word capacity"

# ---------------------------------------------------------------------------
# 3) Split into bank0_lane{0-3}.hex via the real, unmodified splitter --
#    with a program this small it only ever writes bank 0's 4 files, out of
#    the 21 banks the real macro has available.
# ---------------------------------------------------------------------------
say "Splitting into per-lane hex files ..."
python3 "$SPLIT_IMEM_BANKS" "$SMOKE_DIR/smoke_puf.imem.hex" "$IMEM_HEXDIR" 21
[[ -f "$IMEM_HEXDIR/imem_bank0_lane0.hex" ]] || die "Expected imem_bank0_lane0.hex was not produced"
ok "Per-lane hex files in $IMEM_HEXDIR"

# ---------------------------------------------------------------------------
# 4) Build the GLS smoke binary.
# ---------------------------------------------------------------------------
say "Building GLS model -> gls_puf_smoke_build.log (this parses two large gate netlists; can take a while) ..."
fusesoc --cores-root ../.. run --target=sim_gls --tool=verilator --build \
        xinting:playground:secure_boot_v0_puf_smoke_gls > gls_puf_smoke_build.log 2>&1 \
  && ok "GLS build finished" \
  || die "GLS build failed — see gls_puf_smoke_build.log (tail below):
$(tail -n 40 gls_puf_smoke_build.log)"

BUILD_DIR="$SCRIPT_DIR/build/xinting_playground_secure_boot_v0_puf_smoke_gls_0.1/sim_gls-verilator"
BIN="$BUILD_DIR/Vtop_pd_puf_smoke_gls_tb"
[[ -x "$BIN" ]] || die "Expected GLS binary not found at $BIN — check gls_puf_smoke_build.log"

# ---------------------------------------------------------------------------
# 5) Run it — IMEM bank 0 only, no DMEM image, no PUF real-data image
#    (plain reset content is enough to prove the mechanism; pass
#    +gls_realdata_hex=/foss/designs/puf_sim/mc_test/puf_realdata.hex too
#    if a specific/realistic response is wanted for this run).
# ---------------------------------------------------------------------------
say "Running GLS PUF smoke test -> gls_puf_smoke_sim.log ..."
( cd "$BUILD_DIR" && ./Vtop_pd_puf_smoke_gls_tb "+gls_imem_hexdir=$IMEM_HEXDIR" ) \
  > gls_puf_smoke_sim.log 2>&1 \
  && ok "GLS PUF smoke simulation finished" \
  || die "GLS PUF smoke simulation failed — see gls_puf_smoke_sim.log (tail below):
$(tail -n 40 gls_puf_smoke_sim.log)"

echo
say "===== UART output (taped-out top_pd_puf netlist) ====="
if grep -q "UART_RX" gls_puf_smoke_sim.log; then
   grep "UART_RX" gls_puf_smoke_sim.log | sed 's/^/  /'
   STREAM="$(grep -oE "byte=0x[0-9a-f]+ \('.'\)" gls_puf_smoke_sim.log | sed -E "s/.*\('(.)'\)/\1/" | tr -d '\n')"
   echo
   printf '  decoded stream: \033[1;36m%s\033[0m\n' "$STREAM"
   echo
   if [[ "$STREAM" =~ ^EP[0-9A-F]{8}\!$ ]]; then
     printf '  \033[1;32mPASS\033[0m: real IMEM fetched/ran the program, real ESRAM write+readback matched, real PUF path triggered/polled/read back correctly.\n'
   elif [[ "$STREAM" =~ ^eP[0-9A-F]{8}\!$ ]]; then
     printf '  \033[1;33mPARTIAL\033[0m: PUF path worked, but ESRAM readback mismatched (lowercase "e") — inspect gls_puf_smoke_sim.log.\n'
   else
     printf '  \033[1;33mCHECK\033[0m: got a stream but it does not match the expected E/e + P + 8 hex digits + ! pattern.\n'
   fi
else
   echo "  (no UART bytes decoded — check gls_puf_smoke_sim.log; the [GLS_PRELOAD] lines near the top of the log are the first thing to check)"
fi

echo
say "Artifacts (in $BUILD_DIR):"
echo "  gls_puf_smoke_build.log, gls_puf_smoke_sim.log : build/run logs"
ok "Done."
