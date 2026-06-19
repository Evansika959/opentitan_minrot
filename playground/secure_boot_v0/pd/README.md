# secure_boot_v0 — Physical Design (RTL → GDS) with LibreLane

This directory holds the **ASIC implementation** flow for `secure_boot_v0`, kept
separate from the simulation flow (`rtl/`, `tb/`, `sw/`, `test_sw/`) so the two
never pollute each other. Target: **gf180mcuD** — the **wafer.space** shuttle PDK
(chipathon-2026) — via **LibreLane 3.x**.

The flow uses LibreLane's **recommended entrypoint**: a local clone of the
LibreLane repo entered with `nix-shell` (which provides `librelane` + all EDA
tools — `yosys-with-plugins` incl. **slang**, OpenROAD, KLayout, Magic — at pinned
versions). No vendored software (OpenTitan RTL, LibreLane, or the PDK) is modified.

## Approach: harden one block at a time

The full SoC has two hard problems for an open ASIC flow:

1. **SystemVerilog frontend** — Yosys's built-in `read_verilog -sv` won't reliably
   digest OpenTitan SV. **Solved**: set **`USE_SLANG: true`** so `Yosys.Synthesis`
   uses the bundled `read_slang` frontend on the raw SV — no sv2v, no extra tools.
   (sv2v pre-flattening is a documented fallback; see `docs/librelane-reference.md`.)
2. **Memories** — `tlul_sram_if`/`tlul_rom_if` are behavioral (`logic [..] mem[..]`),
   ≈256 KiB each. For ASIC they must become PDK macros. GF180 ships **SRAM IP only**
   (`gf180mcu_fd_ip_sram`, 8-bit wide, max `sram512x8`; 4-wide for a 32-bit word) and
   **no ROM macro** (ROM ⇒ small synthesizable std-cell ROM, or a preloaded SRAM).
   The 64 KiB×3 in the RTL is infeasible — memories must be right-sized. *(Open.)*

So each block is hardened standalone first (logic correctness, timing, the flow),
building toward the full SoC + memory integration.

## How a block is built

`harden_block.sh <blk>` runs the whole flow:

1. **FuseSoC** resolves the block's closure from `blocks/<blk>/*.core` (runs
   OpenTitan's `primgen` to materialize the abstract prim wrappers) and emits an
   ordered verilator `.vc` file list.
2. The script merges `blocks/<blk>/config.json` with that **raw SV file list +
   `USE_SLANG`** into `config.resolved.json` (generated, gitignored).
3. **LibreLane** runs inside `nix-shell` on the resolved config (`--manual-pdk`,
   pointing at the wafer.space gf180mcuD clone) → GDS.

## Layout

```
pd/
├── README.md
├── docs/librelane-reference.md   # captured LibreLane 3.x facts (version-stamped)
├── scripts/
│   ├── env.sh                    # LIBRELANE_DIR/TAG, PDK/PDK_TAG/PDK_ROOT, ll_shell()/ll_env()
│   │                             #   (run `bash scripts/env.sh` to print the env summary)
│   ├── setup_librelane.sh        # clone LibreLane (pinned) + smoke test
│   ├── setup_pdk.sh              # clone wafer.space gf180mcu PDK (pinned tag) for --manual-pdk
│   ├── smoke_test.sh             # smoke test via the clone's nix-shell
│   └── harden_block.sh <blk>     # FuseSoC resolve -> USE_SLANG config -> LibreLane (nix-shell)
├── pdk/                          # wafer.space gf180mcu clone (gitignored, from setup_pdk.sh)
└── blocks/<blk>/                 # one dir per block:
    ├── <blk>.core                #   FuseSoC core: SV closure + toplevel
    ├── <blk>.sdc                 #   block timing constraints (PNR + signoff)
    ├── config.json               #   stable LibreLane knobs (sources injected at run time)
    ├── latch_map.v               #   GF180 latch techmap (PDK ships none; see Notes)
    ├── config.resolved.json      #   generated (gitignored)
    └── runs/                     #   LibreLane outputs (gitignored)
```

Blocks present: **`xbar_tlul_2to4`**, **`ibex_top`**, **`uart`**.

The LibreLane clone lives at `~/tools/librelane` by default; override with
`LIBRELANE_DIR=`. The **PDK** is the wafer.space gf180mcuD distribution cloned to
`pd/pdk/gf180mcu` (gitignored) by `setup_pdk.sh`; override with `PDK`/`PDK_TAG`/`PDK_ROOT`.

## Prerequisites (already satisfied on this machine)

- **Nix** (multi-user daemon) with the **FOSSi binary cache** in `/etc/nix/nix.conf`
  and `flakes` enabled — `nix-shell` substitutes prebuilt binaries.
- **FuseSoC** in the sim flow's venv (`<repo>/.venv-fusesoc`, via `.env.local`) —
  used only to resolve the source closure.

## Quick start

```bash
cd pd
./scripts/setup_librelane.sh        # one-time: clone LibreLane + smoke test
./scripts/setup_pdk.sh              # one-time: clone wafer.space gf180mcuD PDK (~1.2 GB)
./scripts/harden_block.sh ibex_top  # or: xbar_tlul_2to4 | uart   -> GDS
#   synth-only sanity check:  ./scripts/harden_block.sh ibex_top --to Yosys.Synthesis
# results: blocks/<blk>/runs/<tag>/  (final GDS under .../final/gds/)
```

## Status

All blocks below are **GDS, gf180mcuD @ 10 MHz, sign-off on `nom_tt_025C_5v00`**:

| block | die (µm) | utilization | setup WNS | hold | DRC / antenna |
|---|---|---|---|---|---|
| `xbar_tlul_2to4` | 200 × 1060 | 0.66 | + (clean) | met | 0 / 0 |
| `ibex_top` | 1000 × 1000 | 0.61 | +24.4 ns | met | 0 / 0 |
| `uart` | ~497 × 514 (auto) | 0.83 | +26 ns | met | 0 / 0 |

- [x] flow proven: FuseSoC → LibreLane (`USE_SLANG`) → gf180mcuD (`--manual-pdk`)
- [x] `xbar_tlul_2to4`, `ibex_top`, `uart` → GDS, timing-clean
- [ ] memory block (`sram512x8` tiling wrapper) + small std-cell ROM
- [ ] full SoC integration (Ibex + xbar + uart + memories)

## Notes / lessons baked into the configs

- **GF180 missing latch map**: the PDK references a `latch_map.v` it doesn't ship,
  so Yosys can't map OpenTitan `prim_clock_gating`'s D-latch ("1 unmapped cell" on
  Ibex). Each block carries a `latch_map.v` (mapping `$_DLATCH_*` → `latq_1`) wired
  via `SYNTH_LATCH_MAP`.
- **Density** is reported as `design__instance__utilization` in `final/metrics.json`.
  Since std-cell area is ~constant, util = stdcell/core → shrink the core to raise it.
- **Pin-limited blocks** (e.g. the 1080-pin xbar): the die is set by the pin ring,
  not the logic; OpenROAD inserts ~1 I/O buffer per pin (the "buffer bloat"). It's
  benign — it vanishes in-SoC once the block is **flattened** into the top.
- **Signoff** is `nom_tt_025C_5v00` only (`STA_CORNERS`); the slow 4.5 V `ss` corner
  is excluded. Ibex closes 10 MHz at nominal; it would need ~120 ns to cover `ss`.
