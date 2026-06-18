# LibreLane reference (captured 2026-06-17)

Snapshot of the facts that drive this flow. Re-verify against
<https://librelane.readthedocs.io/en/latest/> if things drift.

## Version

- **LibreLane 3.0.4**, released **2026-06-07** (latest stable at capture time).
- 3.0 is the first major release outside Efabless, under the **FOSSi Foundation**.
  Built on **NixOS 25.11** with updated tool versions.
- Successor to OpenLane 2 (and OpenLane 1). API/flow is OpenLane-2-style.

## Install (Nix — recommended)

This machine **already has** Nix (multi-user) with the FOSSi cache configured, so
no installer run is needed. For reference, a fresh install is:

```bash
curl --proto '=https' --tlsv1.2 -fsSL https://artifacts.nixos.org/nix-installer | sh -s -- install \
  --no-confirm --extra-conf "
    extra-substituters = https://nix-cache.fossi-foundation.org
    extra-trusted-public-keys = nix-cache.fossi-foundation.org:3+K59iFwXqKsL7BNu6Guy0v+uTlwsxYQxjspXzqLYQs=
    extra-experimental-features = nix-command flakes
"
git clone https://github.com/librelane/librelane && cd librelane && nix-shell
librelane --smoke-test
```

**This flow uses exactly that recommended path** — a local clone entered via
`nix-shell` — pinned to tag **3.0.4**, kept at `~/tools/librelane` (outside the repo).
`scripts/setup_librelane.sh` does the clone + smoke test; `scripts/env.sh` wraps
runs as `nix-shell "$LIBRELANE_DIR" --run "librelane …"` (helper `ll_shell`).

Other install methods: **Docker** (`librelane --dockerized ...`), **AppImage**,
and **pip** (`pip install librelane`, advanced — you must supply the EDA tools).

## Running a design

```bash
# CLI (config-file driven):
librelane --pdk-root $HOME/.ciel ./designs/<design>/config.json

# Python (Classic flow):
from librelane.flows import Flow
flow = Flow.factory.get("Classic")({
    "PDK": "sky130A",
    "DESIGN_NAME": "spm",
    "VERILOG_FILES": ["./src/spm.v"],
    "CLOCK_PORT": "clk",
    "CLOCK_PERIOD": 10,
}, design_dir=".")
flow.start()
```

- **Classic** flow = the OpenLane-style SequentialFlow: Yosys → OpenROAD →
  KLayout/Magic → GDSII. Good for single-macro / block hardening.
- Outputs land in `<design_dir>/runs/<tag>/`; final GDS under `.../final/gds/`.

## PDK

- Default open PDK: **sky130A** (also sky130B, gf180mcu, ihp-sg13g2).
- PDKs are fetched by **ciel** (the volare successor) into `--pdk-root`
  (default `~/.ciel`). `--smoke-test` downloads what it needs.

## SystemVerilog — two working routes

Yosys's built-in **`read_verilog -sv`** frontend is partial and trips on full
OpenTitan RTL (packages, packed structs, package functions, parameterization).
There are **two** ways around it; we verified both on `xbar_tlul_2to4` (2026-06-17):

1. **`USE_SLANG: true`** *(turnkey — corrects an earlier note here)*. The 3.0.4
   default `Yosys.Synthesis` step is the **`pyosys`** step (`steps/pyosys.py`), which
   exposes a real `bool` `USE_SLANG` var (default `False`, old alias `USE_SYNLIG`)
   plus `SLANG_ARGUMENTS`. When set it does `plugin -i slang; read_slang`. The
   **`yosys-slang` plugin is bundled** (closure pulls `yosys-with-plugins-0.62`).
   Feed raw SV via `VERILOG_FILES` + `VERILOG_INCLUDE_DIRS` (+ `VERILOG_DEFINES`)
   — **no sv2v needed**. Verified: raw 122-file OT closure synthesized clean, 0
   unmapped cells. (Note: the standalone `yosys` CLI on the flake's PATH is 0.33 and
   can't load the 0.62-built `slang.so` — only the in-flow pyosys yosys-0.62 can.)
2. **sv2v pre-flatten** (SystemVerilog → Verilog-2005), then feed the single `.v`.
   Tool-agnostic; LibreLane's own var description calls `read_verilog` the more
   "battle-tested" frontend, and sv2v output uses it. This was the initial approach
   here (it took the xbar all the way to GDS) and remains a valid **fallback**, but
   the live flow uses USE_SLANG, so there is no sv2v step in `scripts/` — sv2v is
   `nixpkgs#haskellPackages.sv2v` if you ever need it.

Either way **FuseSoC still resolves the closure** (file list + primgen-generated
wrappers). USE_SLANG is the simpler pipeline (one fewer tool, no external software);
sv2v is the more conservative one. RTL-reading vars: `VERILOG_FILES`, `VERILOG_DEFINES`,
`VERILOG_INCLUDE_DIRS`, `VERILOG_POWER_DEFINE`, `USE_SLANG`, `SLANG_ARGUMENTS`.

## Key config variables (Classic flow)

| Variable | Meaning |
|---|---|
| `DESIGN_NAME` | top module name |
| `VERILOG_FILES` | list of sources (supports `dir::` + globs) |
| `CLOCK_PORT` / `CLOCK_PERIOD` | clock name / period (ns) |
| `PDK` | e.g. `sky130A` |
| `FP_CORE_UTIL` | floorplan utilization % (lower = easier first run) |

## Doc links

- Docs home: <https://librelane.readthedocs.io/en/latest/>
- Install (Linux/Nix): <https://librelane.readthedocs.io/en/latest/installation/nix_installation/installation_linux.html>
- Flows & config vars: <https://librelane.readthedocs.io/en/latest/reference/flows.html>
- Universal flow vars: <https://librelane.readthedocs.io/en/latest/reference/common_flow_vars.html>
- Step config vars: <https://librelane.readthedocs.io/en/latest/reference/step_config_vars.html>
- Macros/hardening guide: <https://librelane.readthedocs.io/en/latest/usage/>
- GitHub: <https://github.com/librelane/librelane>
- 3.0 announcement: <https://fossi-foundation.org/librelane/blog/2026-03-25-website_release_3-0>
