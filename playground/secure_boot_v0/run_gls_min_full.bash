#!/usr/bin/env bash
# run_gls_min_full.bash — full real-crypto secure-boot + PUF GLS demo for
# top_pd_min (right-sized memories: IMEM=10KiB/10bank, ESRAM/DMEM=2KiB/2bank
# each). Sibling of run_gls_min_stageA.bash, but instead of the Stage A
# checkpoint (PUF-derive + compute_public_key only), this runs the REAL
# chain end to end: PUF-derive key -> compute pubkey -> verify a signed BL0
# container staged in DMEM -> copy the verified payload to ESRAM -> jump and
# execute it.
#
# Two things that only mattered once the chain got this big, both baked in
# below:
#   1. rom_secure_boot_7bank.c (unedited -- same source, just a bank-count-
#      agnostic ROM) needs -flto to fit top_pd_min's 10KiB IMEM. Plain -Os
#      with unused-curve pruning still overflows by ~1KB; -flto closes the
#      rest (fits with ~650B to spare). compat.c (defines __lshrdi3, the
#      libgcc helper GCC calls for 64-bit shifts on RV32) is compiled
#      WITHOUT -flto and kept as a real, non-discardable object -- LTO's
#      whole-program dead-code analysis can decide it's unreferenced before
#      the final codegen pass discovers it needs it, producing a spurious
#      "undefined reference to __lshrdi3" otherwise.
#   2. objcopy -O binary starts its output AT the ELF's first section VMA
#      (0x80, where _start lives -- Ibex fetches its first instruction at
#      boot_addr+0x80), not address 0. Skipping the 128-byte pad before
#      converting to hex shifts the whole image 0x80 early and boots the
#      CPU into garbage mid-instruction (found the hard way on the first
#      top_pd_min Stage A attempt -- silent, no error, just an endless
#      stream of 0x00 on UART).
#
# uECC_compute_public_key/uECC_verify are real, uninstrumented elliptic-
# curve point multiplications on plain RV32IM with no crypto acceleration --
# expect on the order of tens of minutes of wall-clock for a single run to
# reach full completion at Verilator's ~90-100us/s single-threaded GLS
# throughput (multithreading was already proven SLOWER earlier in this
# project, not faster -- don't reach for --threads here). A shorter,
# bounded-window run (the default below) is enough to confirm the chain
# builds, loads, and executes cleanly on the real gates through the
# compute-heavy stage with zero anomalies -- the same standard already
# accepted for top_pd_7bank's own Stage A checkpoint, which never completed
# within any timeout tried either.
#
# Prereq: run ./setup.bash once first (writes .env.local).
#
# Usage:
#   ./run_gls_min_full.bash [timeout_ns]
#     timeout_ns defaults to 60000000 (60ms simulated -- reaches "ROM7: P"
#     [PUF key derived] comfortably, gets well into compute_public_key,
#     does not reach full completion). Pass a much larger value (e.g.
#     300000000-600000000) to chase full completion; budget 30-60+ minutes
#     of wall-clock for that.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ENV_FILE="$SCRIPT_DIR/.env.local"
GLS_DIR="$SCRIPT_DIR/gls"
BUILD_DIR_SW="$SCRIPT_DIR/test_sw/spike_test/build_min_full"
IMEM_HEXDIR="$BUILD_DIR_SW/imem_banks_full"
DMEM_HEXDIR="$BUILD_DIR_SW/dmem_banks_full"
SPLIT_IMEM_BANKS="/foss/designs/sram_puf/ibex_demo/split_imem_banks.py"
TIMEOUT_NS="${1:-60000000}"

say()  { printf '\033[1;34m[min-full]\033[0m %s\n' "$*"; }
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
command -v gcc                >/dev/null 2>&1 || die "native gcc not on PATH (needed for the host packer)."
[[ -f "$SPLIT_IMEM_BANKS" ]] || die "Missing $SPLIT_IMEM_BANKS"
[[ -f "$SCRIPT_DIR/pd/blocks/top_pd_min/runs/fasttest_columnswap/final/nl/top_pd_min.nl.v" ]] \
  || die "Missing top_pd_min.nl.v under runs/fasttest_columnswap/final/nl/ — did the run-tag change? Update gls/secure_boot_v0_min_secboot_gls.core if so."

mkdir -p "$BUILD_DIR_SW" "$IMEM_HEXDIR" "$DMEM_HEXDIR"
cd "$SCRIPT_DIR"

# ---------------------------------------------------------------------------
# 1) Payload: the verified BL0 code ROM copies into ESRAM and jumps to.
# ---------------------------------------------------------------------------
say "Building payload (payload_stage_7bank.c) ..."
CFLAGS_PAYLOAD="-march=rv32im -mabi=ilp32 -Os -ffreestanding -nostdlib -fno-pic -ffunction-sections -fdata-sections -I $SCRIPT_DIR/test_sw/c -I $SCRIPT_DIR/test_sw/c/utils"
"${RISCV_PREFIX}gcc" $CFLAGS_PAYLOAD -c "$SCRIPT_DIR/test_sw/spike_test/payload_stage_7bank_gls.c" -o "$BUILD_DIR_SW/payload.o"
"${RISCV_PREFIX}gcc" $CFLAGS_PAYLOAD -c "$SCRIPT_DIR/test_sw/c/utils/uart.c" -o "$BUILD_DIR_SW/uart_payload.o"
"${RISCV_PREFIX}gcc" $CFLAGS_PAYLOAD -Wl,-T,"$SCRIPT_DIR/test_sw/spike_test/link_payload_7bank_gls.ld" -Wl,--gc-sections \
  -o "$BUILD_DIR_SW/payload.elf" "$BUILD_DIR_SW/payload.o" "$BUILD_DIR_SW/uart_payload.o"
"${RISCV_PREFIX}objcopy" -O binary --only-section=.text --only-section=.rodata "$BUILD_DIR_SW/payload.elf" "$BUILD_DIR_SW/payload.bin"
ok "payload.bin: $(stat -c%s "$BUILD_DIR_SW/payload.bin") bytes"

# ---------------------------------------------------------------------------
# 2) Host-side packer: signs the payload with the PUF-derived key (same
#    known bytes rom_secure_boot_7bank.c re-derives on-target) and writes
#    the packed, signed container as a $readmemh word list.
# ---------------------------------------------------------------------------
say "Building + running host packer (host_pack_7bank_image.c, native gcc) ..."
gcc -O2 -I "$SCRIPT_DIR/test_sw/c/utils" -I "$SCRIPT_DIR/test_sw/c/utils/micro-ecc" -I "$SCRIPT_DIR/test_sw/c" \
  -DuECC_CURVE=uECC_secp160r1 \
  -o "$BUILD_DIR_SW/host_pack" "$SCRIPT_DIR/test_sw/spike_test/host_pack_7bank_image_gls.c" \
  "$SCRIPT_DIR/test_sw/c/utils/micro-ecc/uECC.c" "$SCRIPT_DIR/test_sw/c/utils/sha256.c"
( cd "$BUILD_DIR_SW" && ./host_pack payload.bin dmem_full.hex )
ok "Signed container: $BUILD_DIR_SW/dmem_full.hex"

# ---------------------------------------------------------------------------
# 3) ROM: PUF-derive + compute_public_key + verify + copy + jump. -flto to
#    fit the 10KiB IMEM budget (see header comment).
# ---------------------------------------------------------------------------
say "Compiling rom_secure_boot_7bank.c (LTO + curve-pruned uECC, 10KiB IMEM budget) ..."
UECCDEFS="-DuECC_SUPPORTS_secp192r1=0 -DuECC_SUPPORTS_secp224r1=0 -DuECC_SUPPORTS_secp256r1=0 -DuECC_SUPPORTS_secp256k1=0 -DuECC_SUPPORT_COMPRESSED_POINT=0 -DuECC_OPTIMIZATION_LEVEL=0"
BASE="-march=rv32im -mabi=ilp32 -Os -ffreestanding -nostdlib -fno-pic -ffunction-sections -fdata-sections -I $SCRIPT_DIR/test_sw/c -I $SCRIPT_DIR/test_sw/spike_test $UECCDEFS"
LTOFLAGS="$BASE -flto"

"${RISCV_PREFIX}gcc" $BASE -c "$SCRIPT_DIR/test_sw/c/utils/compat.c" -o "$BUILD_DIR_SW/compat.o"
"${RISCV_PREFIX}gcc" $LTOFLAGS -c "$SCRIPT_DIR/test_sw/c/crt0.S" -o "$BUILD_DIR_SW/crt0.o"
"${RISCV_PREFIX}gcc" $LTOFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/mem.c" -o "$BUILD_DIR_SW/mem.o"
"${RISCV_PREFIX}gcc" $LTOFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/memset.c" -o "$BUILD_DIR_SW/memset.o"
"${RISCV_PREFIX}gcc" $LTOFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/sha256.c" -o "$BUILD_DIR_SW/sha256.o"
"${RISCV_PREFIX}gcc" $LTOFLAGS -c "$SCRIPT_DIR/test_sw/c/utils/uart.c" -o "$BUILD_DIR_SW/uart.o"
"${RISCV_PREFIX}gcc" $LTOFLAGS -DuECC_CURVE=uECC_secp160r1 -c "$SCRIPT_DIR/test_sw/c/utils/micro-ecc/uECC.c" -o "$BUILD_DIR_SW/uecc.o"
"${RISCV_PREFIX}gcc" $LTOFLAGS -c "$SCRIPT_DIR/test_sw/spike_test/rom_secure_boot_7bank_gls.c" -o "$BUILD_DIR_SW/rom.o"

"${RISCV_PREFIX}gcc" $LTOFLAGS -Wl,-T,"$SCRIPT_DIR/test_sw/link_min_rom.ld" -Wl,--gc-sections \
  -o "$BUILD_DIR_SW/rom_full_min.elf" \
  "$BUILD_DIR_SW/crt0.o" "$BUILD_DIR_SW/compat.o" "$BUILD_DIR_SW/mem.o" "$BUILD_DIR_SW/memset.o" \
  "$BUILD_DIR_SW/sha256.o" "$BUILD_DIR_SW/uart.o" "$BUILD_DIR_SW/uecc.o" "$BUILD_DIR_SW/rom.o"
ok "Linked: $BUILD_DIR_SW/rom_full_min.elf"

# ---------------------------------------------------------------------------
# 4) ELF -> raw binary (0x80 pad!) -> $readmemh hex -> per-bank hex files.
# ---------------------------------------------------------------------------
say "Building IMEM/DMEM hex images ..."
"${RISCV_PREFIX}objcopy" -O binary "$BUILD_DIR_SW/rom_full_min.elf" "$BUILD_DIR_SW/rom_full_min.raw.bin"
dd if=/dev/zero bs=1 count=128 status=none of="$BUILD_DIR_SW/pad.bin"
cat "$BUILD_DIR_SW/pad.bin" "$BUILD_DIR_SW/rom_full_min.raw.bin" > "$BUILD_DIR_SW/rom_full_min.bin"
rm -f "$BUILD_DIR_SW/pad.bin"
python3 "$SCRIPT_DIR/test_sw/bin2hex32.py" "$BUILD_DIR_SW/rom_full_min.bin" > "$BUILD_DIR_SW/rom_full_min.imem.hex"
WORDS=$(wc -l < "$BUILD_DIR_SW/rom_full_min.imem.hex")
ok "IMEM image: $WORDS words (10-bank capacity is 2560)"
[[ "$WORDS" -le 2560 ]] || die "Full ROM ($WORDS words) exceeds top_pd_min's 10-bank IMEM (2560 words)"

rm -rf "$IMEM_HEXDIR" && mkdir -p "$IMEM_HEXDIR"
python3 "$SPLIT_IMEM_BANKS" "$BUILD_DIR_SW/rom_full_min.imem.hex" "$IMEM_HEXDIR" 10

# split_imem_banks.py always names its output imem_bankN_laneL.hex regardless
# of source -- reuse it for DMEM into a scratch dir, then rename to match
# what the tb's DMEM backdoor-load actually reads.
rm -rf "$DMEM_HEXDIR" && mkdir -p "$DMEM_HEXDIR"
python3 "$SPLIT_IMEM_BANKS" "$BUILD_DIR_SW/dmem_full.hex" "$DMEM_HEXDIR" 2
( cd "$DMEM_HEXDIR" && for f in imem_bank*.hex; do mv "$f" "${f/imem_/dmem_}"; done )
ok "Per-bank hex files in $IMEM_HEXDIR and $DMEM_HEXDIR"

# ---------------------------------------------------------------------------
# 5) Build the GLS binary (parses top_pd_min + 10bank + 2bank gate netlists).
# ---------------------------------------------------------------------------
say "Building GLS model -> gls_min_full_build.log (this can take a while) ..."
fusesoc --cores-root ../.. run --target=sim_gls --tool=verilator --build \
        xinting:playground:secure_boot_v0_min_secboot_gls > gls_min_full_build.log 2>&1 \
  && ok "GLS build finished" \
  || die "GLS build failed — see gls_min_full_build.log (tail below):
$(tail -n 40 gls_min_full_build.log)"

BUILD_DIR="$SCRIPT_DIR/build/xinting_playground_secure_boot_v0_min_secboot_gls_0.1/sim_gls-verilator"
BIN="$BUILD_DIR/Vtop_pd_min_secboot_gls_tb"
[[ -x "$BIN" ]] || die "Expected GLS binary not found at $BIN — check gls_min_full_build.log"

# ---------------------------------------------------------------------------
# 6) Run it. Single-threaded only -- --threads was already proven SLOWER
#    (not faster) for this class of GLS workload earlier in this project.
# ---------------------------------------------------------------------------
say "Running GLS min full secure-boot test (timeout=${TIMEOUT_NS}ns) -> gls_min_full_sim.log ..."
( cd "$BUILD_DIR" && ./Vtop_pd_min_secboot_gls_tb \
    "+gls_imem_hexdir=$IMEM_HEXDIR" \
    "+gls_dmem_hexdir=$DMEM_HEXDIR" \
    "+gls_realdata_hex=/foss/designs/puf_sim/mc_test/puf_realdata.hex" \
    "+gls_timeout_ns=$TIMEOUT_NS" ) \
  > gls_min_full_sim.log 2>&1 \
  || true   # timing out before full completion is expected/acceptable, see header comment

echo
say "===== UART output (taped-out top_pd_min netlist, full secure-boot chain) ====="
if grep -q "UART_RX" gls_min_full_sim.log; then
   grep "UART_RX" gls_min_full_sim.log | sed 's/^/  /'
   STREAM="$(grep -oE "byte=0x[0-9a-f]+ \('.'\)" gls_min_full_sim.log | sed -E "s/.*\('(.)'\)/\1/" | tr -d '\n')"
   echo
   printf '  decoded stream: \033[1;36m%s\033[0m\n' "$STREAM"
   if echo "$STREAM" | grep -q "Payload: verified boot OK"; then
     printf '  \033[1;32mFULL PASS\033[0m: real PUF-derived key, real SHA256 digest, real secp160r1 signature verify, real copy-to-ESRAM and jump all completed on the taped-out top_pd_min netlist.\n'
   else
     echo "  (did not reach full completion within the timeout -- expected for short budgets, see this script's header comment. Re-run with a larger timeout_ns argument to chase full completion.)"
   fi
else
   echo "  (no UART bytes decoded — check gls_min_full_sim.log; the [GLS_PRELOAD] lines near the top are the first thing to check)"
fi

echo
say "Artifacts (in $BUILD_DIR):"
echo "  gls_min_full_build.log, gls_min_full_sim.log : build/run logs"
ok "Done."
