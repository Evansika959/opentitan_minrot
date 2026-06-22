# RTL → GDS, step by step (student walkthrough)

This is a hands-on tour of how `secure_boot_v0` goes from **SystemVerilog source** to a
**manufacturable layout (GDSII)** using **LibreLane** + the **gf180mcuD** open PDK. Every
stage below has a *separate, runnable command* so you can stop, look at the output, and
understand what each tool did before moving on.

Run everything from the `pd/` directory:

```bash
cd /home/xinting/Desktop/opentitan_minrot/playground/secure_boot_v0/pd
```

---

## 0. What "RTL → GDS" means

| You start with | You end with |
|---|---|
| **RTL** — behavioral SystemVerilog (`always`, `+`, `mem[]`) | **GDSII** — polygons on silicon layers (metal, poly, diffusion) |

In between, a chain of tools transforms the design:

```
RTL ─► [synthesis] ─► gate netlist ─► [floorplan] ─► [power grid] ─►
       [placement] ─► [clock tree] ─► [routing] ─► [signoff: DRC/LVS/STA] ─► GDS
```

LibreLane (the open-source flow built on **Yosys**, **OpenROAD**, **KLayout**, **Magic**,
**netgen**) runs this chain as ~77 small **steps**. You can run the whole chain with one
command, or stop after any step with `--to <StepID>` to inspect intermediate results.

This SoC is built **hierarchically**: each block becomes a GDS *hard macro* on its own,
then the macros are assembled into the chip (`top_pd`). So the flow is run **once per
block**, then **once for the top**.

---

## 1. One-time setup

```bash
# 1a. Clone LibreLane (pinned 3.0.4) and validate its toolchain via nix-shell.
./scripts/setup_librelane.sh

# 1b. Clone the wafer.space gf180mcuD PDK (~1.2 GB) for --manual-pdk.
./scripts/setup_pdk.sh

# 1c. (optional) print the resolved environment (paths, tool status).
bash scripts/env.sh
```

`setup_librelane.sh` puts LibreLane at `~/tools/librelane`; everything runs *inside* its
`nix-shell` (the helper `ll_shell "<cmd>"` in `env.sh` does that). No tools are installed
globally and no vendor code is modified.

---

## 2. Harden one block (we'll use `xbar_tlul_2to4` — it's the fastest)

### 2a. The whole flow in one command

```bash
./scripts/harden_block.sh xbar_tlul_2to4
```

This does three things (see `harden_block.sh`):
1. **FuseSoC** resolves the block's source closure from `blocks/xbar_tlul_2to4/*.core`
   (running OpenTitan `primgen` to generate the prim wrappers) → an ordered `.vc` file list.
2. The script merges `blocks/xbar_tlul_2to4/config.json` with that **raw SV list +
   `USE_SLANG: true`** into `config.resolved.json`.
3. **LibreLane** runs the full Classic flow in `nix-shell` → GDS.

Result lands in `blocks/xbar_tlul_2to4/runs/<timestamp>/final/`. Set a shell variable to
point at the newest run so the inspection commands below work:

```bash
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1); echo "$RUN"
```

### 2b. The same flow, one stage at a time

Each command below runs the flow **up to and including** one stage, then stops, so you can
look at what that stage produced. (Each `--to` is a fresh run that redoes the earlier
stages — fine for a small block. To *resume* instead of redo, see the Appendix.)

```bash
# ── Stage 1: SYNTHESIS  (RTL → gate netlist of gf180 standard cells) ────────────
./scripts/harden_block.sh xbar_tlul_2to4 --to Yosys.Synthesis
#   inspect: the gate netlist + cell/area report
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1)
ls   "$RUN"/*-yosys-synthesis/
grep -E "Number of cells|chip area" "$RUN"/*-yosys-synthesis/*.log | tail
#   key idea: Yosys maps your RTL onto real cells (nand, dff, ...). "0 unmapped cells" = good.
```

```bash
# ── Stage 2: FLOORPLAN  (define the die/core area + standard-cell rows) ─────────
./scripts/harden_block.sh xbar_tlul_2to4 --to OpenROAD.Floorplan
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1)
grep -iE "die area|core area" "$RUN"/*-openroad-floorplan/*.log | head
#   key idea: the empty chip canvas. DIE_AREA comes from config.json (FP_SIZING:absolute).
```

```bash
# ── Stage 3: POWER GRID  (VDD/VSS straps, rails, and the core ring) ─────────────
./scripts/harden_block.sh xbar_tlul_2to4 --to OpenROAD.GeneratePDN
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1)
grep -iE "PDN-|ring|channel" "$RUN"/*-openroad-generatepdn/*.log | head
#   key idea: power is delivered before cells are placed. This block uses default M4/M5
#   straps + PDN_CORE_RING (the peripheral ring the chip-top later ties onto).
```

```bash
# ── Stage 4: PLACEMENT  (pins on the edges, then cells onto the rows) ───────────
./scripts/harden_block.sh xbar_tlul_2to4 --to OpenROAD.DetailedPlacement
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1)
#   pin sides come from blocks/xbar_tlul_2to4/pin_order.cfg (W=hosts, E=devices, ...)
grep -iE "utilization|HPWL|overflow" "$RUN"/*-openroad-globalplacement/*.log | tail
#   key idea: global placement spreads cells to minimize wirelength; detailed legalizes them.
```

```bash
# ── Stage 5: CLOCK TREE SYNTHESIS  (balanced clock to every flop) ───────────────
./scripts/harden_block.sh xbar_tlul_2to4 --to OpenROAD.CTS
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1)
grep -iE "clock buffer|sinks|skew" "$RUN"/*-openroad-cts/*.log | head
#   key idea: TritonCTS inserts clock buffers so the clock reaches all flops with low skew.
```

```bash
# ── Stage 6: ROUTING  (global plan, then exact wires on metal layers) ───────────
./scripts/harden_block.sh xbar_tlul_2to4 --to OpenROAD.DetailedRouting
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1)
grep -hoE "Number of violations = [0-9]+" "$RUN"/*-openroad-detailedrouting/*.log | tail
#   key idea: global routing finds congestion-free paths; detailed routing draws real metal.
#   "Number of violations = 0" at the end = clean routing.
```

```bash
# ── Stage 7: SIGNOFF  (extract parasitics, final STA, DRC, LVS) ─────────────────
./scripts/harden_block.sh xbar_tlul_2to4          # full run (through all checkers + GDS)
RUN=$(ls -dt blocks/xbar_tlul_2to4/runs/RUN_* | head -1)
grep -E "timing__setup__ws,|timing__hold__ws,|route__drc_errors,|design__lvs_error__count,|antenna__violating__nets," \
     "$RUN"/final/metrics.csv
#   key ideas:
#     RCX        extracts wire R/C from the routed metal,
#     STAPostPNR re-checks timing with those real parasitics,
#     KLayout/Magic DRC check the polygons obey the foundry rules,
#     netgen LVS checks the layout matches the netlist ("Circuits match uniquely").
```

The finished macro is in `"$RUN"/final/`: `gds/`, `lef/` (abstract for the top), `nl/`
(gate netlist), `lib/` (timing model), `def/`, `spef/`.

Repeat 2a for the other blocks (each → its own GDS):

```bash
for b in ibex_top uart tlul_sram_if_macro; do ./scripts/harden_block.sh $b; done
```

> **Block-specific notes:** `ibex_top`/`uart` carry a `latch_map.v` (gf180 ships none);
> `tlul_sram_if_macro` wraps 4 vendor SRAM macros (its own `pdn_cfg.tcl` bridges their M3
> pins to M4) and runs with `RUN_MAGIC_DRC: false` (a foundry-abstract false-positive).

---

## 3. Export the finished macros

Before the chip top can use the blocks, collect their physical views:

```bash
./scripts/export_macros.sh
ls macros/                       # one dir per block + macros.json
cat macros/macros.json           # the MACROS manifest (gds/lef/lib/... absolute paths)
```

This copies each block's `final/` views into `macros/<blk>/` so `top_pd` can instance them
as hard macros.

---

## 4. Integrate the chip top (`top_pd`)

`top_pd` is the same flow, but instead of synthesizing the blocks it **places them as hard
macros**. The placements + macro views live in `blocks/top_pd/config.json` (`MACROS`), and
the blocks appear to synthesis as blackbox `stubs/` so they are kept, not flattened.

```bash
./scripts/harden_block.sh top_pd --skip KLayout.Render --skip OpenROAD.IRDropReport
RUN=$(ls -dt blocks/top_pd/runs/RUN_* | head -1)
grep -E "route__drc_errors,|klayout__drc_error__count,|design__lvs_error__count,|antenna__violating__nets,|timing__setup__ws," \
     "$RUN"/final/metrics.csv
grep -i "match" "$RUN"/*-netgen-lvs/reports/lvs.netgen.rpt | tail -2     # "Circuits match uniquely"
```

Why the two `--skip`s: `KLayout.Render` aborts on the multi-macro hierarchy, and IR-drop is
run separately (next section). The **PDN at the top** uses the *halo method*: the macros are
placed hub-and-spoke with channels between them; the chip M4/M5 grid runs in those channels
and ties onto each block's **core ring** — so no straps cross block interiors and no power
shapes orphan (which is what makes LVS match).

The chip GDS: `"$RUN"/final/gds/top_pd.gds`.

---

## 5. Reviewing results

```bash
RUN=$(ls -dt blocks/top_pd/runs/RUN_* | head -1)

# 5a. all signoff metrics at a glance
column -t -s, "$RUN"/final/metrics.csv | grep -iE "drc|lvs|antenna|timing__(setup|hold)|power|util"

# 5b. DRC detail (KLayout, full gf180 deck)
python3 -c "import json;d=json.load(open('$RUN/*-klayout-drc/reports/drc.klayout.json'));print('DRC total:',d['total'])"

# 5c. LVS verdict
sed -n '/Final result/,+1p' "$RUN"/*-netgen-lvs/reports/lvs.netgen.rpt

# 5d. IR-drop (power integrity) — run as a single extra step on the finished run
./scripts/harden_block.sh top_pd --last-run --only OpenROAD.IRDropReport
grep -iE "Percentage|Worstcase IR" "$RUN"/*irdropreport/*.log | head
```

### Render an image of the layout (headless)

```bash
RUN=$(ls -dt blocks/top_pd/runs/RUN_* | head -1)
OR=$(ls -d /nix/store/*openroad-2026-02-17-python3*/bin/openroad | head -1)
cat > /tmp/render.tcl <<TCL
read_db $RUN/final/odb/top_pd.odb
save_image -area {0 0 3200 3200} -width 4000 $PWD/top_pd.png
exit
TCL
QT_QPA_PLATFORM=offscreen $OR -gui /tmp/render.tcl
#   -> top_pd.png   (or open final/gds/top_pd.gds in KLayout if you have a display)
```

---

## Appendix A — useful LibreLane flags

`harden_block.sh <blk> <extra flags…>` passes the extra flags straight to `librelane`:

| Flag | Effect |
|---|---|
| `--to <StepID>` | run up to and including this step, then stop |
| `--from <StepID>` | start from this step (needs prior state; pair with `--last-run`) |
| `--only <StepID>` | run just this one step on an existing run |
| `--skip <StepID>` | run everything except this step |
| `--last-run` | resume the most recent run instead of starting fresh |

Resume example (don't redo synthesis just to inspect floorplan):

```bash
./scripts/harden_block.sh xbar_tlul_2to4 --to Yosys.Synthesis
ll_shell "librelane --pdk gf180mcuD --pdk-root $PWD/pdk/gf180mcu --manual-pdk \
          --last-run --from OpenROAD.Floorplan --to OpenROAD.Floorplan \
          blocks/xbar_tlul_2to4/config.resolved.json"
```

## Appendix B — the step → stage map

| Stage | Key step IDs (and run dir) |
|---|---|
| Synthesis | `Yosys.Synthesis` (`*-yosys-synthesis`) |
| Floorplan | `OpenROAD.Floorplan` (`13-…`) |
| Power grid | `OpenROAD.GeneratePDN` (`21-…`) |
| I/O + global place | `OpenROAD.IOPlacement`, `Odb.CustomIOPlacement`, `OpenROAD.GlobalPlacement` (`24–28`) |
| Detailed place | `OpenROAD.DetailedPlacement` (`34-…`) |
| Clock tree | `OpenROAD.CTS`, `OpenROAD.ResizerTimingPostCTS` (`35–37`) |
| Routing | `OpenROAD.GlobalRouting`, `OpenROAD.DetailedRouting` (`39`, `45`) |
| Fill + extract + STA | `OpenROAD.FillInsertion`, `OpenROAD.RCX`, `OpenROAD.STAPostPNR` (`53`, `55`, `56`) |
| Stream out (GDS) | `Magic.StreamOut`, `KLayout.StreamOut` (`58`, `59`) |
| Signoff DRC/LVS | `Magic.DRC`, `KLayout.DRC`, `Netgen.LVS` (`65`, `66`, `71`) |
| IR drop | `OpenROAD.IRDropReport` (`57`) |

(See the full ordered list in any `blocks/<blk>/runs/<tag>/` — each `NN-tool-step/` dir is
one step, in order.)

## Appendix C — further reading

- `docs/librelane-reference.md` — captured LibreLane 3.x facts (frontends, PDK, config vars).
- `../README.md` — this flow's overview, layout, and current status.
- LibreLane docs: <https://librelane.readthedocs.io/en/latest/>
</content>
