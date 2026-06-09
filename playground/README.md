# Playground — minimal Ibex SoCs for Verilator

This directory holds three self-contained, hand-built SoC examples that grow in
complexity. Each one wraps the **lowRISC Ibex** core with a **TL-UL crossbar**,
some memories, and OpenTitan peripherals, then simulates it under **Verilator**
via **FuseSoC**. The RISC-V program that runs on Ibex is built separately from C
and/or assembly and handed to the RTL as a `$readmemh` hex image.

| Example | What it adds | Bus fabric | Peripherals |
|---|---|---|---|
| [`pure_ibex_uart`](#1-pure_ibex_uart) | The smallest working SoC: fetch from IMEM, load/store to DMEM, print over UART | 1→2 xbar | UART |
| [`secure_boot_v0`](#2-secure_boot_v0) | A ROM that verifies a **signed** ROM_EXT (SHA-256 + ECDSA P-256) and jumps to it | 2→4 xbar | UART, ROM, exec-SRAM, data-SRAM |
| [`secure_boot_v1`](#3-secure_boot_v1) | Same secure-boot chain **plus crypto accelerators** | 2→6 xbar | + HMAC, + OTBN |

All three share the same build/run shape, so read the **[Common concepts](#common-concepts)**
section once, then jump to the example you care about.

---

## Prerequisites

| Tool | Used for | Notes |
|---|---|---|
| **Verilator** ≥ 5.0 | Compiling/running the simulation | `verilator --version` |
| **FuseSoC** | Resolving cores and driving Verilator | `pip install fusesoc` |
| **RISC-V GCC** (`riscv32-` or `riscv64-unknown-elf-`) | Building the Ibex programs | The SW Makefiles auto-detect either prefix |
| **OpenSSL** | Generating the signing key + signing boot images | `secure_boot_*` only |
| **Python 3** | Hex packing / image tools | Standard library only |
| **picolibc** (riscv) | `stdint.h` etc. for the C tests | `secure_boot_*/test_sw`; path is overridable (see below) |

> **Heads-up about the current machine:** at the time of writing `fusesoc` and the
> `riscv*-unknown-elf-gcc` toolchains are **not on `PATH`** here (only Verilator and
> Python are). Install / activate them (e.g. a Python venv for FuseSoC and a RISC-V
> GCC in `PATH`) before the steps below will work end-to-end.

---

## ⚠️ Fix the hard-coded paths first (one-time)

The RTL tops load their memory images with **absolute paths** that were baked in on
the original author's machine:

```
/home/xinting/opentitan_minrot/playground/...
```

This repository now lives at `/home/xinting/Desktop/opentitan_minrot/` (note the extra
`Desktop/`), so `$readmemh` will silently fail to find the images and Ibex will execute
zeros. Two `test_sw/Makefile`s have the same stale path.

> **For `secure_boot_v0` you don't need to do this by hand** — `secure_boot_v0/run_v0.bash`
> rewrites the RTL image paths to the correct local location on every run (and the
> `test_sw/Makefile` path bug is already fixed). See
> [Quick start with the helper scripts](#quick-start-with-the-helper-scripts). The manual
> patch below is for the other examples / doing it yourself:

Patch them all to match wherever you cloned the repo:

```bash
# Run from the repo root. REPO is the absolute path to this checkout.
REPO=$(git rev-parse --show-toplevel)
grep -rlZ '/home/xinting/opentitan_minrot/' playground \
     --include='*.sv' --include='Makefile' \
  | xargs -0 sed -i "s|/home/xinting/opentitan_minrot/|$REPO/|g"
```

Affected files (for reference):

- `pure_ibex_uart/rtl/pure_ibex_uart_top.sv` — `IMEM_INIT_HEX`, `DMEM_INIT_HEX`
- `secure_boot_v0/rtl/top.sv` and `secure_boot_v1/rtl/top.sv` — `IMEM_INIT_HEX`, `DMEM_INIT_HEX`
- `secure_boot_v0/test_sw/Makefile` and `secure_boot_v1/test_sw/Makefile` — the `--target` of `replace_dmem.py`

Alternatively, override `IMEM_INIT_HEX` / `DMEM_INIT_HEX` per run instead of editing files
(see [Pointing the sim at a different program](#pointing-the-sim-at-a-different-program)).

---

## Common concepts

### The build/run pipeline

```
   C / .S  ──gcc──▶  .elf  ──objcopy──▶  .bin  ──bin2hex32.py──▶  *.hex
                                                                    │
                                                  $readmemh (IMEM_INIT_HEX,
                                                            DMEM_INIT_HEX)
                                                                    ▼
   *.core (FuseSoC)  ──▶  Verilator build  ──▶  ./Vtop  ──▶  waves + UART console
        (RTL + tb_sv + tb_cpp)
```

- **`<example>/Makefile`** — the top-level "run the simulation" Makefile. `make run`
  shells out to FuseSoC, which reads the `*.core` file, pulls in the lowRISC IP
  dependencies, and builds + runs the Verilator model.
- **`<example>/sw/` and `<example>/test_sw/`** — separate Makefiles that build the
  RISC-V program(s) into `hex/` images. **You build software first**, then run the sim.
- **`tb/`** — the testbench. `*_tb.sv` is the SystemVerilog wrapper around the DUT and
  `*.cpp` (`sim_main.cpp` / `main.cpp`) is the Verilator C++ harness that drives the
  clock/reset and writes the FST waveform.

### Clock / reset / timeout

Every example is driven from the C++ harness, not SystemVerilog:

- 10 MHz clock (100 time units per cycle).
- `rst_n` released at cycle **50**.
- `uart_rx` held idle-high.
- Simulation stops at a cycle cap: **200 k** (`pure_ibex_uart`), **2 M**
  (`secure_boot_v0`), **100 k** (`secure_boot_v1`). Bump this in the relevant
  `tb/*.cpp` if your program needs longer.

### The UART "cheat" console

Real UART byte-timing is slow to simulate, so the testbenches snoop the TL-UL bus and
`$write` any byte the program stores to `UART.WDATA` straight to stdout. So anything the
program "prints" over UART shows up directly in the simulation log — no baud decoding
needed. (The programs still configure a realistic NCO for 115200 baud @ 10 MHz = `0x2F30`.)

### Outputs of a run

- **`*.fst`** — waveform (open with GTKWave / Surfer). `make copy` lifts it out of the
  FuseSoC build tree into the example directory.
- **`sim.log`** — full simulation log (the `secure_boot_*` Makefiles redirect into this;
  `pure_ibex_uart` prints to the terminal).
- **`esram_dump.hex`** — `secure_boot_*` dump the exec-SRAM contents at end of sim (via a
  DPI call) so you can inspect what the ROM copied in.

### Pointing the sim at a different program

The image paths are RTL parameters, so you can override them at elaboration time without
editing files, e.g.:

```bash
fusesoc --cores-root ../.. run --target=sim --tool=verilator \
  xinting:playground:secure_boot_v1 \
  --IMEM_INIT_HEX=$PWD/test_sw/hex/hmac_demo.imem.hex \
  --DMEM_INIT_HEX=$PWD/test_sw/hex/hmac_demo.dmem.hex
```

### Regenerating the TL-UL crossbar

The crossbars under `rtl/autogen/` are generated by OpenTitan's `tlgen.py` from the
address map in `hjson/`. To regenerate after changing the map:

```bash
make xbar_gen        # secure_boot_v0 / secure_boot_v1
# = python ../../util/tlgen.py -t ./hjson/<map>.hjson --o ./rtl/autogen/
```

---

## 1. `pure_ibex_uart`

The minimal SoC: Ibex + a 1→2 TL-UL crossbar splitting the address space into a low
half (IMEM/DMEM) and a high half (UART).

**Memory map** (`pure_ibex_uart_top.sv`, `tb`):

| Region | Base | Notes |
|---|---|---|
| IMEM  | `0x0000_0000` | instruction SRAM, init from `imem.hex` |
| DMEM  | `0x1000_0000` | data SRAM, init from `dmem.hex` |
| UART  | `0x2000_0000` | OpenTitan UART (`CTRL` @ `+0x10`, `STATUS` @ `+0x14`, `WDATA` @ `+0x1C`) |

**Software** lives in `sw/` and is pure assembly under `sw/assembly/`:

- `smoke.S` — store `0xdeadbeef` to DMEM, read it back, spin (a bus sanity check).
- `uart.S` — configure the UART and print a string (drives the cheat console).
- `start.S` — trivial "load a constant and loop" program.

The RTL initializes IMEM/DMEM from `imem.hex` / `dmem.hex` **in the example root**, so
the workflow is: build a test → copy its hex into the root as `imem.hex` → run.

```bash
cd pure_ibex_uart

# 1) Build the program(s) → sw/hex/<name>.hex
cd sw
make uart            # or: make smoke   /   make all
cd ..

# 2) Wire the chosen program in as the IMEM image.
#    (dmem.hex of all-zeros is already present and fine for these tests.)
cp sw/hex/uart.hex imem.hex

# 3) Build + run the simulation
make run             # fusesoc + verilator; prints to the terminal
make copy            # (optional) copy mini.fst into this dir for waveform viewing
```

**Expected output:** RVFI instruction-retire traces (`[TB][RVFI] ...`), TL-UL UART
request logs, and—for `uart.S`—the printed string via the cheat console.

Helper: `decode_rv32.py` is a tiny RV32I/M disassembler — pipe hex words into it to read
back what an image contains.

---

## 2. `secure_boot_v0`

A minimal **secure boot** chain. A ROM (in IMEM) verifies a signed **ROM_EXT** image that
was packed into data-SRAM, then copies it into exec-SRAM and jumps to it; ROM_EXT in turn
can verify and launch **BL0**. Verification is SHA-256 over a bound header+payload, checked
with ECDSA P-256 (`micro-ecc`) against a trusted public key compiled into the ROM.

**Memory map** (`hjson/tlul_2to4.hjson`, two hosts: instruction + data):

| Device | Base | Size | Role |
|---|---|---|---|
| ROM (IMEM)   | `0x0000_0000` | 64 KiB | boot ROM code |
| exec-SRAM    | `0x0001_0000` | 64 KiB | where verified images are copied & run (`EXEC_BASE`) |
| data-SRAM    | `0x0002_0000` | 64 KiB | RW data + the packed boot images |
| UART         | `0x0003_0000` | 64 KiB | console |

Within data-SRAM: `BOOT_IMG_BASE = 0x0002_1000` (ROM_EXT container),
`BL0_IMG_BASE = 0x0002_3000`.

### Quick start with the helper scripts

Two scripts automate the whole flow and are written to work on any machine (they discover
the toolchain, pin FuseSoC, fix the paths, build, and run):

```bash
cd secure_boot_v0
./setup.bash      # one-time: find RISC-V GCC / Verilator / OpenSSL, make a FuseSoC venv,
                  #           init the micro-ecc submodule, write .env.local
./run_v0.bash     # build+sign images, build the ROM, wire up rtl/top.sv, run the sim,
                  #           then print the UART console output
```

`setup.bash` is idempotent and writes `secure_boot_v0/.env.local` recording the toolchain
it found; `run_v0.bash` reads that. The simulation runs to a 2,000,000-cycle cap and takes
a few minutes; the full log lands in `sim.log`.

**Expected output** (the boot chain prints short per-stage markers over UART):

```
decoded stream: sJPEXTJPB
  ROM      s = start,  J = before payload copy,  P = after copy -> jump to ROM_EXT
  ROM_EXT  EXT = entered,  J = before copy,  P = after copy -> jump to BL0
  BL0      B = entered
```

Seeing `sJPEXTJPB` means the full chain **ROM → ROM_EXT → BL0** executed, with each stage's
verified payload copied into exec-SRAM and entered (RVFI shows the PC running at
`0x0001_xxxx`).

> **Security caveat:** the ROM image that actually runs (`test_sw/c/rom.c`) is a **debug
> build with the on-target ECDSA verify commented out**, so it copies + jumps without
> checking the signature. The images are still genuinely signed and packed by `sw/`
> (`pack_image.py` + OpenSSL), and `run_v0.bash` syncs the matching public key into the ROM
> source. To exercise *real* verification, re-enable the `uECC_verify(...)` block near the
> top of `test_sw/c/rom.c` (and the `compute_digest` call above it), then rebuild — expect a
> much longer run, since software P-256 verify on Ibex is many cycles; you may need to raise
> the cycle cap in `tb/main.cpp`.

### Doing it manually / the two software trees

- **`sw/`** — the *real* boot flow and the image packer:
  - `boot/rom.c`, `boot/rom_ext.c`, `boot/bl0.c` — ROM / ROM_EXT / BL0 sources.
  - `tools/pack_image.py` — generates a P-256 keypair (via OpenSSL), signs ROM_EXT + BL0,
    packs them into a **data-SRAM init hex** (`build/d_sram.hex`), and emits
    `trusted_pubkey.h` for the ROM to compile against.
  - `crypto/micro-ecc/` — vendored ECDSA library.
- **`test_sw/`** — standalone unit tests that exercise one thing each, built as separate
  IMEM/DMEM images (`c/`, `assembly/`):
  - `dmem_test.c` — write/read-back a DMEM pattern.
  - `uart_test.c` — UART TX bring-up.
  - `stack_test.c` — stack pointer / `crt0` sanity.
  - `uecc_test.c`, `uecc_test_64.c` — on-target ECDSA verify; `uecc_test_host.c` builds
    on the host for a reference check.

### Build & run

`run_v0.bash` performs exactly these steps; here they are spelled out (run from
`secure_boot_v0/`, with the RISC-V GCC and the FuseSoC venv on `PATH`):

```bash
# A) Build + sign the boot images → sw/build/d_sram.hex and sw/boot/trusted_pubkey.h
#    (RISCV_PREFIX auto-detects; pass it explicitly if you have an unusual prefix)
make -C sw all

# B) Sync the freshly-generated public key into the ROM source, so the ROM would
#    verify against the key that actually signed the image.
cp sw/boot/trusted_pubkey.h test_sw/c/utils/trusted_pubkey.h

# C) Build the ROM image + overlay the signed image into the combined DMEM init.
#    Produces test_sw/hex/rom.imem.hex and rom_with_image.dmem.hex (what rtl/top.sv loads).
make -C test_sw rom
#   To build a standalone unit test instead:  make -C test_sw dmem_test

# D) Point the RTL at those images on THIS machine (Verilator $readmemh needs an abs path),
#    then run the simulation (log → sim.log).
#    (run_v0.bash does this rewrite for you; or edit rtl/top.sv's IMEM/DMEM_INIT_HEX.)
make run
make copy            # (optional) copy secure_boot_v0.fst here
```

**Expected output** (via the cheat console / `[TB][UART_RX]` lines in `sim.log`): the
per-stage markers **`sJPEXTJPB`** — `s J P` from the ROM, `EXT J P` from ROM_EXT, `B` from
BL0 — i.e. the full **ROM → ROM_EXT → BL0** chain. The exec-SRAM contents are dumped to
`esram_dump.hex` at the end. (See the [security caveat](#quick-start-with-the-helper-scripts)
about the disabled on-target signature check.)

> **Note:** `hex/` and `sw/build/` are **build artifacts** (not committed), so steps A–C
> must run before the first `make run`. The `make rom` path bug and the `sw/Makefile`'s
> hard-coded `riscv64-` prefix are already fixed; the only remaining machine-specific bit is
> the `rtl/top.sv` image path (handled by `run_v0.bash`, or the
> [manual patch](#️-fix-the-hard-coded-paths-first-one-time)).

The C tests use the host's RISC-V `stdint.h` and picolibc headers. If picolibc isn't at
the default location, override it:

```bash
make all PICOLIBC_DIR=/path/to/picolibc/riscv64-unknown-elf
```

---

## 3. `secure_boot_v1`

Everything in `secure_boot_v0`, extended with two OpenTitan crypto IPs on a wider (2→6)
crossbar, so the boot/test software can use hardware acceleration.

**Memory map** (`hjson/tlul_main.hjson`) — same as v0 plus:

| Device | Base | Size |
|---|---|---|
| HMAC | `0x0004_0000` | 64 KiB |
| OTBN | `0x0005_0000` | 64 KiB |

**Extra demos** (`test_sw/c/`):

- `hmac_demo.c` — register-level **SHA-256** using the HMAC IP (no-key hashing): config →
  `hash_start` → stream the message through `MSG_FIFO` → `hash_process` → read `DIGEST_*`.
- `otbn_demo.c` — loads a tiny program into **OTBN** IMEM, executes it, and checks
  `ERR_BITS`.

`rtl/top.sv` defaults to loading the **`otbn_demo`** images. Build whichever demo you want
and either copy/rename it to match, or override `IMEM_INIT_HEX`/`DMEM_INIT_HEX` at run time.

### Build & run

```bash
cd secure_boot_v1

# Build a demo (HMAC needs no micro-ecc; ECDSA tests need USE_UECC=1)
cd test_sw
make otbn_demo       # → hex/otbn_demo.{imem,dmem}.hex   (matches the RTL default)
#   make hmac_demo
#   make uecc_test USE_UECC=1
cd ..

# Run
make run             # log → sim.log
make copy            # (optional) copy secure_boot_v1.fst here
```

The full signed-boot flow (`sw/` + `test_sw/ make rom`) works the same as v0 if you want
the ROM to drive the boot instead of running a bare demo.

---

## Make-target reference

**Top-level `<example>/Makefile`:**

| Target | Action |
|---|---|
| `make run` (default) | FuseSoC → Verilator build + run |
| `make copy` | Copy the generated `*.fst` waveform into the example dir |
| `make xbar_gen` | Regenerate the TL-UL crossbar from `hjson/` (secure_boot only) |

**`pure_ibex_uart/sw/Makefile`:**

| Target | Action |
|---|---|
| `make <name>` | Build `hex/<name>.hex` from `assembly/<name>.S` |
| `make all` | Build every test in `assembly/` |
| `make clean` | Remove `build/` and `hex/` |

**`secure_boot_*/sw/Makefile`** (boot images):

| Target | Action |
|---|---|
| `make all` | Keypair + sign + pack → `build/d_sram.hex` (+ `boot/trusted_pubkey.h`) |
| `make imem` | Build the ROM IMEM hex |
| `make pubkey` | Emit `trusted_pubkey.h` only |
| `make clean` | Remove `build/` and the generated header |

**`secure_boot_*/test_sw/Makefile`** (unit tests / ROM):

| Target | Action |
|---|---|
| `make <name>` | Build `hex/<name>.{hex,imem.hex,dmem.hex}` from `c/<name>.c` or `assembly/<name>.S` |
| `make all` | Build all tests |
| `make rom` | Build the ROM image and patch the signed `d_sram.hex` into `rom_with_image.dmem.hex` |
| `USE_UECC=1` | (v1) link in `micro-ecc` for ECDSA tests |
| `make clean` | Remove `build/` and `hex/` |

---

## Troubleshooting

- **Ibex executes zeros / nothing prints** — the `$readmemh` path is wrong. Re-check the
  [path-fix step](#️-fix-the-hard-coded-paths-first-one-time); the image paths in
  `rtl/*.sv` must point at hex files that actually exist.
- **`fusesoc: command not found`** — install/activate FuseSoC (`pip install fusesoc`); the
  Makefiles call it directly.
- **`riscv*-unknown-elf-gcc: command not found`** — put a RISC-V GCC on `PATH`, or pass
  `RISCV_PREFIX=...` to the SW Makefiles.
- **C test fails on `stdint.h`/picolibc** — pass `PICOLIBC_DIR=/your/path` to the
  `test_sw` build.
- **Program hits the cycle-cap timeout** — raise the cap in the relevant `tb/*.cpp`
  (`if (cycle >= ...)`).
- **`d_sram.hex` / `hex/` missing** — those are build outputs; run the `sw` and `test_sw`
  builds before `make run`.
