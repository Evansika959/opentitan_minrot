#!/usr/bin/env bash
# run_gls_min_stageA.bash — Stage A real-crypto GLS check for top_pd_min
# (right-sized memories: IMEM=10KiB/10bank, ESRAM/DMEM=2KiB/2bank each).
#
# Mirrors the top_pd_7bank Stage A checkpoint (compiled-C crt0 + PUF-derive
# + uECC_compute_public_key, no DMEM/signature-verify yet) using the SAME
# source file (test_sw/c/rom_7bank_stageA.c, unedited -- it never touches
# DMEM/ESRAM so it has no dependency on their size, only IMEM's) relinked
# against link_min_rom.ld (10KiB budget instead of 7KiB). Confirmed to fit
# with margin: .text+.rodata+.bss = ~7.6KB of the 10KB budget.
#
# Prereq: run ./setup.bash once first (writes .env.local).
#
# Usage:
#   ./run_gls_min_stageA.bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
ENV_FILE="$SCRIPT_DIR/.env.local"
GLS_DIR="$SCRIPT_DIR/gls"
BUILD_DIR_SW="$SCRIPT_DIR/test_sw/spike_test/build_min_stageA"
IMEM_HEXDIR="$BUILD_DIR_SW/imem_banks"
SPLIT_IMEM_BANKS="/foss/designs/sram_puf/ibex_demo/split_imem_banks.py"

say()  { printf '\033[1;34m[min-stageA]\033[0m %s\n' "$*"; }
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
[[ -f "$SCRIPT_DIR/pd/blocks/top_pd_min/runs/fasttest_columnswap/final/nl/top_pd_min.nl.v" ]] \
  || die "Missing top_pd_min.nl.v under runs/fasttest_columnswap/final/nl/ — did the run-tag change? Update gls/secure_boot_v0_min_secboot_gls.core if so."

mkdir -p "$BUILD_DIR_SW" "$IMEM_HEXDIR"
cd "$SCRIPT_DIR"

# ---------------------------------------------------------------------------
# 1) Compile Stage A ROM against the 10KiB IMEM budget.
# ---------------------------------------------------------------------------
say "Compiling rom_7bank_stageA.c against link_min_rom.ld (10KiB IMEM) ..."
CFLAGS="-march=rv32im -mabi=ilp32 -Os -ffreestanding -nostdlib -fno-pic -ffunction-sections -fdata-sections -I $SCRIPT_DIR/test_sw/c -I $SCRIPT_DIR/test_sw/c/utils"

"${RISCV_PREFIX}gcc" $CFLAGS -c "$SCRIPT_DIR/test_sw/c/crt0.S" -o "$BUILD_DIR_SW/crt0.o"
"${RISCV_PREFIX}gcc" $CFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/compat.c" -o "$BUILD_DIR_SW/compat.o"
"${RISCV_PREFIX}gcc" $CFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/mem.c" -o "$BUILD_DIR_SW/mem.o"
"${RISCV_PREFIX}gcc" $CFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/memset.c" -o "$BUILD_DIR_SW/memset.o"
"${RISCV_PREFIX}gcc" $CFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/uart.c" -o "$BUILD_DIR_SW/uart.o"
"${RISCV_PREFIX}gcc" $CFLAGS -DuECC_CURVE=uECC_secp160r1 -c "$SCRIPT_DIR/test_sw/c/utils/micro-ecc/uECC.c" -o "$BUILD_DIR_SW/uecc.o"
"${RISCV_PREFIX}gcc" $CFLAGS -c "$SCRIPT_DIR/test_sw/c/rom_7bank_stageA.c" -o "$BUILD_DIR_SW/rom.o"

"${RISCV_PREFIX}gcc" $CFLAGS -Wl,-T,"$SCRIPT_DIR/test_sw/link_min_rom.ld" -Wl,--gc-sections \
  -o "$BUILD_DIR_SW/rom_stageA_min.elf" \
  "$BUILD_DIR_SW/crt0.o" "$BUILD_DIR_SW/compat.o" "$BUILD_DIR_SW/mem.o" "$BUILD_DIR_SW/memset.o" \
  "$BUILD_DIR_SW/uart.o" "$BUILD_DIR_SW/uecc.o" "$BUILD_DIR_SW/rom.o"
ok "Linked: $BUILD_DIR_SW/rom_stageA_min.elf"

# ---------------------------------------------------------------------------
# 2) ELF -> raw binary -> $readmemh hex -> per-bank/per-lane hex files.
#
# objcopy -O binary starts its output AT the ELF's first section VMA (0x80,
# where _start lives -- Ibex fetches its first instruction at boot_addr+0x80),
# not at address 0. Without prepending that 128-byte gap, byte 0 of the raw
# binary is _start's own first byte, which then gets loaded as if it were
# IMEM address 0 -- shifting the whole image 0x80 early and making the CPU
# boot into garbage mid-instruction (same fix run_gls_7bank_smoke.bash's
# pad.bin step already does; found by a real failed run here first, where
# the netlist ran forever spamming UART with 0x00 instead of "ROM7:...").
# ---------------------------------------------------------------------------
say "Building IMEM hex image ..."
"${RISCV_PREFIX}objcopy" -O binary "$BUILD_DIR_SW/rom_stageA_min.elf" "$BUILD_DIR_SW/rom_stageA_min.raw.bin"
dd if=/dev/zero bs=1 count=128 status=none of="$BUILD_DIR_SW/pad.bin"
cat "$BUILD_DIR_SW/pad.bin" "$BUILD_DIR_SW/rom_stageA_min.raw.bin" > "$BUILD_DIR_SW/rom_stageA_min.bin"
rm -f "$BUILD_DIR_SW/pad.bin"
python3 "$SCRIPT_DIR/test_sw/bin2hex32.py" "$BUILD_DIR_SW/rom_stageA_min.bin" > "$BUILD_DIR_SW/rom_stageA_min.imem.hex"
WORDS=$(wc -l < "$BUILD_DIR_SW/rom_stageA_min.imem.hex")
ok "IMEM image: $BUILD_DIR_SW/rom_stageA_min.imem.hex ($WORDS words, 10-bank capacity is 2560)"
[[ "$WORDS" -le 2560 ]] || die "Stage A ROM ($WORDS words) exceeds top_pd_min's 10-bank IMEM (2560 words)"

say "Splitting into per-lane hex files ..."
python3 "$SPLIT_IMEM_BANKS" "$BUILD_DIR_SW/rom_stageA_min.imem.hex" "$IMEM_HEXDIR" 10
[[ -f "$IMEM_HEXDIR/imem_bank0_lane0.hex" ]] || die "Expected imem_bank0_lane0.hex was not produced"
ok "Per-lane hex files in $IMEM_HEXDIR"

# ---------------------------------------------------------------------------
# 3) Build the GLS binary (parses the top_pd_min + 10bank + 2bank gate
#    netlists; slower than the smoke test's single small netlist).
# ---------------------------------------------------------------------------
say "Building GLS model -> gls_min_stageA_build.log (this can take a while) ..."
fusesoc --cores-root ../.. run --target=sim_gls --tool=verilator --build \
        xinting:playground:secure_boot_v0_min_secboot_gls > gls_min_stageA_build.log 2>&1 \
  && ok "GLS build finished" \
  || die "GLS build failed — see gls_min_stageA_build.log (tail below):
$(tail -n 40 gls_min_stageA_build.log)"

BUILD_DIR="$SCRIPT_DIR/build/xinting_playground_secure_boot_v0_min_secboot_gls_0.1/sim_gls-verilator"
BIN="$BUILD_DIR/Vtop_pd_min_secboot_gls_tb"
[[ -x "$BIN" ]] || die "Expected GLS binary not found at $BIN — check gls_min_stageA_build.log"

# ---------------------------------------------------------------------------
# 4) Run it — IMEM preload only (Stage A never touches DMEM). Pass
#    +gls_realdata_hex=/foss/designs/puf_sim/mc_test/puf_realdata.hex for a
#    realistic PUF response instead of all-zero reset content (all-zero
#    produces an invalid EC key and a "ROM: NO KEY" die(), same failure
#    mode hit earlier on top_pd_7bank).
# ---------------------------------------------------------------------------
say "Running GLS min Stage A test -> gls_min_stageA_sim.log ..."
( cd "$BUILD_DIR" && ./Vtop_pd_min_secboot_gls_tb \
    "+gls_imem_hexdir=$IMEM_HEXDIR" \
    "+gls_realdata_hex=/foss/designs/puf_sim/mc_test/puf_realdata.hex" ) \
  > gls_min_stageA_sim.log 2>&1 \
  && ok "GLS min Stage A simulation finished" \
  || die "GLS min Stage A simulation failed — see gls_min_stageA_sim.log (tail below):
$(tail -n 40 gls_min_stageA_sim.log)"

echo
say "===== UART output (taped-out top_pd_min netlist, Stage A) ====="
if grep -q "UART_RX" gls_min_stageA_sim.log; then
   grep "UART_RX" gls_min_stageA_sim.log | sed 's/^/  /'
   STREAM="$(grep -oE "byte=0x[0-9a-f]+ \('.'\)" gls_min_stageA_sim.log | sed -E "s/.*\('(.)'\)/\1/" | tr -d '\n')"
   echo
   printf '  decoded stream: \033[1;36m%s\033[0m\n' "$STREAM"
else
   echo "  (no UART bytes decoded — check gls_min_stageA_sim.log; the [GLS_PRELOAD] lines near the top are the first thing to check)"
fi

echo
say "Artifacts (in $BUILD_DIR):"
echo "  gls_min_stageA_build.log, gls_min_stageA_sim.log : build/run logs"
ok "Done."
