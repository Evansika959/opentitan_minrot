# secure_boot_v0 — Physical Design (RTL → GDS) with LibreLane

This directory holds the **ASIC implementation** flow for `secure_boot_v0`, kept
separate from the simulation flow (`rtl/`, `tb/`, `sw/`, `test_sw/`) so the two
never pollute each other. Target: **gf180mcuD** — the **wafer.space** shuttle PDK
(chipathon-2026) — via **LibreLane 3.0.4**.

> **New here?** Read **[`docs/rtl-to-gds-walkthrough.md`](docs/rtl-to-gds-walkthrough.md)** —
> a step-by-step, command-by-command tour of the whole flow for students.

The flow uses LibreLane's **recommended entrypoint**: a local clone of the
LibreLane repo entered with `nix-shell` (which provides `librelane` + all EDA
tools — `yosys-with-plugins` incl. **slang**, OpenROAD, KLayout, Magic, netgen — at
pinned versions). No vendored software (OpenTitan RTL, LibreLane, or the PDK) is modified.

## The design

`secure_boot_v0` is a minimal OpenTitan-derived Root-of-Trust SoC:

```
        Ibex core ──(2 host ports via ibex_to_tlul adapters)──► xbar ──► ROM  (imem)
                                                                  ├─────► eSRAM (esram)
                                                                  ├─────► DSRAM (dmem)
                                                                  └─────► UART
```

It is built **hierarchically**: each block is hardened on its own into a GDS *hard
macro*, then the six macro instances are assembled at the chip top (`top_pd`).

| Block dir | Module | Role |
|---|---|---|
| `ibex_top/` | `ibex_top` | RISC-V core (pure std-cell) |
| `xbar_tlul_2to4/` | `xbar_tlul_2to4` | TL-UL crossbar (2 hosts → 4 devices) |
| `tlul_sram_if_macro/` | `tlul_sram_if_macro` | 1 KiB TL-UL SRAM = 4× gf180 `sram256x8` (used ×3: imem/esram/dmem) |
| `uart/` | `uart` | UART peripheral |
| `top_pd/` | `top_pd` | full-chip integration: the six macros + glue |

## Two hard problems (both solved)

1. **SystemVerilog frontend** — Yosys's built-in `read_verilog -sv` won't reliably
   digest OpenTitan SV. **Solved** with **`USE_SLANG: true`** so `Yosys.Synthesis`
   reads the raw SV via the bundled `yosys-slang` plugin — no sv2v, no extra tools.
   (sv2v pre-flattening is a documented fallback; see `docs/librelane-reference.md`.)
2. **Memories** — the sim RTL uses behavioral arrays (`logic [..] mem[..]`, ~256 KiB).
   For ASIC they become PDK macros. **Solved**: `tlul_sram_if_macro` tiles 4× the gf180
   `gf180mcu_fd_ip_sram__sram256x8` (8-bit-wide IP) into a 1 KiB / 32-bit block, hardened
   once and instanced three times. (gf180 ships **SRAM IP only, no ROM macro** — the ROM is
   just an SRAM instance whose contents are fixed at integration.)

## The flow, end to end

```
 RTL (.sv)                                              hard macros            full chip
 ─────────                                              ───────────            ─────────
 FuseSoC closure ─► harden_block.sh <blk> ─► GDS  ─►  export_macros.sh  ─►  harden_block.sh top_pd ─► GDS
   (.core)            (per block, USE_SLANG)            (macros/*.lef/gds/lib)   (MACROS + halo PDN)
```

1. **Per block** — `harden_block.sh <blk>`:
   (a) FuseSoC resolves the block's SV closure from `blocks/<blk>/*.core` (runs OpenTitan
   `primgen`) and emits a verilator `.vc` file list; (b) the script merges
   `blocks/<blk>/config.json` with that raw-SV list + `USE_SLANG` into
   `config.resolved.json`; (c) LibreLane runs in `nix-shell` (`--manual-pdk`,
   wafer.space gf180mcuD) → GDS in `blocks/<blk>/runs/<tag>/final/`.
2. **Export** — `export_macros.sh` harvests each finished block's `final/` views
   (gds/lef/lib/spice/nl) into `macros/<blk>/` and writes `macros/macros.json`.
3. **Top** — `harden_block.sh top_pd` integrates the six macro instances (placed via
   `MACROS` in `top_pd/config.json`) with glue logic → full-chip GDS.

### PDN: the "halo" method

Every block is hardened with the **default M4/M5 power grid + a peripheral core ring**
(`PDN_CORE_RING: true`). At the top, the blocks are placed **hub-and-spoke with channels
between them**; the chip-level M4/M5 grid runs in those channels and **ties onto each
block's ring** (macro-grid + `PDN_MACRO_CONNECTIONS`) — no power straps are forced over
block interiors, so nothing orphans. See the walkthrough for the full rationale.

## Layout

```
pd/
├── README.md
├── docs/
│   ├── rtl-to-gds-walkthrough.md   # ← student step-by-step (read this)
│   └── librelane-reference.md      # captured LibreLane 3.x facts (version-stamped)
├── scripts/
│   ├── env.sh                # paths + ll_shell()/ll_env()  (run `bash scripts/env.sh` for a summary)
│   ├── setup_librelane.sh    # one-time: clone LibreLane (pinned) + smoke test
│   ├── setup_pdk.sh          # one-time: clone wafer.space gf180mcu PDK (pinned) for --manual-pdk
│   ├── smoke_test.sh         # LibreLane smoke test via the clone's nix-shell
│   ├── harden_block.sh <blk> # FuseSoC resolve → USE_SLANG config → LibreLane (one block or top_pd)
│   └── export_macros.sh      # harvest finished blocks → macros/ + macros.json (for the top)
├── pdk/                      # wafer.space gf180mcu clone (gitignored, from setup_pdk.sh)
├── macros/                   # exported hard-macro views (gitignored, from export_macros.sh)
└── blocks/<blk>/             # one dir per block:
    ├── <blk>.core            #   FuseSoC core: SV closure + toplevel
    ├── <blk>.sdc             #   block timing constraints (PNR + signoff)
    ├── config.json           #   stable LibreLane knobs (RTL sources injected at run time)
    ├── pin_order.cfg         #   I/O pin sides (std-cell blocks)
    ├── pdn_cfg.tcl           #   custom PDN (only tlul_sram_if_macro + top_pd)
    ├── latch_map.v           #   GF180 latch techmap (ibex_top, uart; see Notes)
    ├── stubs/                #   (top_pd only) blackbox stubs so synth keeps macros
    ├── config.resolved.json  #   generated (gitignored)
    └── runs/                 #   LibreLane outputs (gitignored)
```

The LibreLane clone lives at `~/tools/librelane` by default (`LIBRELANE_DIR=` to relocate);
the PDK is cloned to `pd/pdk/gf180mcu` by `setup_pdk.sh` (`PDK`/`PDK_TAG`/`PDK_ROOT` to override).

## Prerequisites (already satisfied on this machine)

- **Nix** (multi-user daemon) with the **FOSSi binary cache** in `/etc/nix/nix.conf`
  and `flakes` enabled — `nix-shell` substitutes prebuilt binaries instead of building.
- **FuseSoC** in the sim flow's venv (`<repo>/.venv-fusesoc`, via `.env.local`) —
  used only to resolve the source closure.

## Quick start

```bash
cd pd
./scripts/setup_librelane.sh                 # one-time: clone LibreLane + smoke test
./scripts/setup_pdk.sh                        # one-time: clone wafer.space gf180mcuD PDK (~1.2 GB)

# harden every block (each → GDS):
for b in ibex_top xbar_tlul_2to4 uart tlul_sram_if_macro; do ./scripts/harden_block.sh $b; done
./scripts/export_macros.sh                    # collect the finished macros
./scripts/harden_block.sh top_pd \
    --skip KLayout.Render --skip OpenROAD.IRDropReport   # integrate the full chip → GDS

# results: blocks/<blk>/runs/<tag>/final/gds/*.gds
```

For the step-by-step explanation of what each phase does (synthesis, floorplan, PDN,
placement, CTS, routing, signoff) and how to run them one at a time, see
**[`docs/rtl-to-gds-walkthrough.md`](docs/rtl-to-gds-walkthrough.md)**.

## Status (2026-06, gf180mcuD @ 10 MHz, signoff corner `nom_tt_025C_5v00`)

| block | die (µm) | util | setup WNS | hold WNS | route/KLayout DRC | LVS | antenna |
|---|---|---|---|---|---|---|---|
| `ibex_top` | 1000 × 1000 | 0.66 | +23.6 ns | +0.48 ns | 0 / 0 | match | 0 |
| `xbar_tlul_2to4` | 500 × 500 | 0.55 | +46.7 ns | +0.71 ns | 0 / 0 | match | 0 |
| `uart` | 640 × 580 | 0.57 | +53.0 ns | +0.37 ns | 0 / 0 | match | 0 |
| `tlul_sram_if_macro` | 1100 × 900 | 0.66 | +65.6 ns | +0.68 ns | 0 / 0 | match | 0 |
| **`top_pd`** | **3200 × 3200** | 0.48 | +15.5 ns | +0.80 ns | 0 / 0 | **match uniquely** | 0 |

- [x] flow proven: FuseSoC → LibreLane (`USE_SLANG`) → gf180mcuD (`--manual-pdk`)
- [x] all four block types → GDS, timing-clean
- [x] memory block (`tlul_sram_if_macro`, 4× `sram256x8`) and small/ROM via SRAM instance
- [x] full SoC integration (`top_pd`): clean route/KLayout DRC + LVS (halo PDN)

**Known gaps (shuttle milestone, not full signoff):** single-corner timing only
(`nom_tt`; no ss/ff); `top_pd` has **86 unfixed max-slew violations** on long inter-block
nets (slew gate disabled) and a **core ring that spills outside the die**; IR-drop is
approximate (no pads / `VSRC_LOC_FILES`); Magic DRC is waived on the SRAM vendor abstract
(KLayout DRC + LVS are the signoff). See `docs/rtl-to-gds-walkthrough.md` §"Reviewing results".

## Notes / lessons baked into the configs

- **GF180 missing latch map**: the PDK references a `latch_map.v` it doesn't ship, so
  Yosys can't map OpenTitan `prim_clock_gating`'s D-latch. `ibex_top` and `uart` carry a
  `latch_map.v` (`$_DLATCH_*` → `latq_1`) wired via `SYNTH_LATCH_MAP`.
- **Density** is reported as `design__instance__utilization` in `final/metrics.json`.
- **SRAM block** runs with `RUN_MAGIC_DRC: false` — Magic's open deck false-positives
  `M3.1` on the foundry SRAM abstract power pins; KLayout DRC (full deck) + LVS are clean.
- **`top_pd`** must run with `--skip KLayout.Render` (the renderer aborts on the multi-macro
  hierarchy); IR-drop is run separately (`--last-run --only OpenROAD.IRDropReport`).
</content>
