# secure_boot_v0 — Physical Design (RTL → GDS) with LibreLane

This directory holds the **ASIC implementation** flow for `secure_boot_v0`, kept
separate from the simulation flow (`rtl/`, `tb/`, `sw/`, `test_sw/`) so the two
never pollute each other. Target: **gf180mcuD** (the wafer.space shuttle PDK, for
chipathon-2026) via **LibreLane 3.x**. (Initial bring-up was on sky130A; some result
notes below still cite those numbers and are being re-run on gf180mcuD.)

The flow uses LibreLane's **recommended entrypoint**: a local clone of the
LibreLane repo entered with `nix-shell` (which provides `librelane` + all EDA
tools — `yosys-with-plugins` incl. **slang**, OpenROAD, KLayout, Magic — at pinned
versions). No vendored software (OpenTitan RTL or LibreLane) is modified.

## Strategy: derisk on one block first

The full SoC has two hard problems for an open ASIC flow (see
`docs/librelane-reference.md`):

1. **Behavioral memories** — `tlul_sram_if`/`tlul_rom_if` model RAM/ROM as
   `logic [31:0] mem [0:(1<<16)-1]` (≈256 KiB *each*, ×3). Infeasible as flops;
   must become PDK SRAM/ROM macros. (Still open — the SoC's real fork.)
2. **SystemVerilog frontend** — Yosys's built-in `read_verilog -sv` won't reliably
   digest OpenTitan SV. **Solved**: set **`USE_SLANG: true`** so the `Yosys.Synthesis`
   step uses the bundled `read_slang` frontend on the raw SV — no sv2v, no extra
   tools. (sv2v pre-flattening is the documented fallback; see the reference doc.)

So we prove the **FuseSoC → LibreLane (slang) → gf180mcuD** pipeline on a small but
representative block (`xbar_tlul_2to4`: packages + structs + prim deps +
assertions, **no memory**) before scaling to `uart` and then the full SoC.

## How a block is built

`harden_block.sh <blk>` runs the whole flow:

1. **FuseSoC** resolves the block's closure from `blocks/<blk>/*.core` (this runs
   OpenTitan's `primgen` to materialize the abstract prim wrappers) and emits an
   ordered verilator `.vc` file list.
2. The script merges `blocks/<blk>/config.json` with that **raw SV file list +
   `USE_SLANG`** into `config.resolved.json` (generated, gitignored).
3. **LibreLane** runs inside `nix-shell` on the resolved config → GDS.

## Layout

```
pd/
├── README.md
├── docs/librelane-reference.md   # captured LibreLane 3.x facts (version-stamped)
├── scripts/
│   ├── env.sh                    # LIBRELANE_DIR/TAG, PDK_ROOT, ll_shell()/ll_env() helpers
│   │                             #   (run `bash scripts/env.sh` to print the env summary)
│   ├── setup_librelane.sh        # clone LibreLane (pinned) + smoke test
│   ├── setup_pdk.sh              # clone wafer.space gf180mcu PDK (pinned tag) for --manual-pdk
│   ├── smoke_test.sh             # smoke test via the clone's nix-shell
│   └── harden_block.sh <blk>     # FuseSoC resolve -> USE_SLANG config -> LibreLane (nix-shell)
├── pdk/                          # wafer.space gf180mcu clone (gitignored, from setup_pdk.sh)
└── blocks/
    └── xbar_tlul_2to4/
        ├── xbar_tlul_2to4.core   # FuseSoC core: defines the SV closure + toplevel
        ├── xbar.sdc              # block timing constraints (PNR + signoff)
        ├── config.json           # stable LibreLane knobs (sources injected at run time)
        ├── config.resolved.json  # generated (gitignored)
        └── runs/                 # LibreLane outputs (gitignored)
```

The LibreLane clone lives at `~/tools/librelane` by default (outside this repo, next
to the RISC-V toolchain); override with `LIBRELANE_DIR=...`. The **PDK** is the
wafer.space **gf180mcuD** distribution cloned to `pd/pdk/gf180mcu` (gitignored) by
`setup_pdk.sh`, used via `librelane --manual-pdk`; override with `PDK`/`PDK_TAG`/`PDK_ROOT`.

## Prerequisites (already satisfied on this machine)

- **Nix** (multi-user daemon) with the **FOSSi binary cache** in `/etc/nix/nix.conf`
  (`nix-cache.fossi-foundation.org`) and `flakes` enabled — `nix-shell` substitutes
  prebuilt binaries instead of building from source.
- **FuseSoC** in the sim flow's venv (`<repo>/.venv-fusesoc`, via `.env.local`) — used
  only to resolve the source closure.

## Quick start

```bash
cd pd
./scripts/setup_librelane.sh              # one-time: clone LibreLane + smoke test
./scripts/setup_pdk.sh                    # one-time: clone wafer.space gf180mcuD PDK (~1.2 GB)
./scripts/harden_block.sh xbar_tlul_2to4  # whole flow -> GDS
#   synth-only sanity check:  ./scripts/harden_block.sh xbar_tlul_2to4 --to Yosys.Synthesis
# results: blocks/xbar_tlul_2to4/runs/<tag>/  (final GDS under .../final/gds/)
```

## Status

- [x] LibreLane docs captured (`docs/librelane-reference.md`)
- [x] Workspace scaffolded
- [x] Smoke test / PDK fetch (LibreLane 3.0.4, sky130A)
- [x] **`xbar_tlul_2to4` → GDS** — SV→GDS pipeline proven (2026-06-17)
- [x] re-confirmed `xbar_tlul_2to4` → GDS via **nix-shell + USE_SLANG** (no sv2v)
- [x] **`xbar_tlul_2to4` timing closed @ 20 MHz** with real SDC (`xbar.sdc`):
      setup WNS **+17.9 ns**, hold met, 0 DRC/antenna/slew/cap — sign-off clean
- [ ] `uart` → GDS
- [ ] full SoC (needs the memory-macro decision)

### Derisk result — `xbar_tlul_2to4` (final: nix-shell + USE_SLANG, 20 MHz)

FuseSoC → LibreLane (slang) → sky130A works end to end on OpenTitan SV, fully
sign-off clean:

| | |
|---|---|
| DRC / antenna | **0 / 0** |
| Setup WNS / TNS | **+17.9 ns / 0** (closed @ 20 MHz, real `xbar.sdc`) |
| Hold WNS / TNS | **+0.19 ns / 0** (met) |
| Max slew / cap violations | **none** |
| Std cells | 4,713 |
| Die | 400×400 µm (pad-limited: 1056-bit TL-UL struct interface), ~19% util |

Lessons baked into the scripts/config:
- **`USE_SLANG: true`** reads raw OpenTitan SV directly (validated: 0 unmapped
  cells), so the flow needs no sv2v and stays inside LibreLane's nix-shell.
- `VERILOG_DEFINES: ["SYNTHESIS=1"]` keeps OT assertion modules out of synthesis.
- Wide struct interfaces are **pad-limited** — size the die by pin perimeter
  (`FP_SIZING: absolute` + `DIE_AREA`), not core utilization.
- A context-aware SDC (`blocks/xbar_tlul_2to4/xbar.sdc`) — single clock, `scanmode_i`
  false-path, on-chip 15% I/O budget (not 4 ns off-chip), realistic driver/load,
  0.10 ns uncertainty — cut setup **TNS from −209 ns to −42 ns (~5×)**. WNS plateaus
  at ~−1.7 ns @ 50 MHz: the worst path is a ~15.6 ns combinational host→device
  feedthrough (decode + mux + integrity) plus route buffering across the pad-limited
  die — **structural/floorplan, not SDC**. Standalone Fmax ≈ 45 MHz; the design's
  documented clock is **10 MHz** (sim TB), at which the block closes with huge margin.
  Real xbar timing is set in-SoC (flattened/placed with neighbours), not standalone.
