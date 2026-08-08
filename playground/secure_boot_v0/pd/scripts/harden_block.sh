#!/usr/bin/env bash
# Whole RTL->GDS flow for one block, the LibreLane nix-shell way.
#
#   1. FuseSoC resolves the SV closure (runs primgen) and emits a file list.
#   2. We merge blocks/<blk>/config.json with that raw-SV file list + USE_SLANG
#      into a generated config.resolved.json.
#   3. LibreLane runs inside `nix-shell` on the resolved config.
#
# Usage: harden_block.sh <block> [extra librelane args, e.g. --to Yosys.Synthesis]
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"

BLOCK="${1:?usage: harden_block.sh <block> [librelane args...]}"; shift || true
EXTRA="$*"
BDIR="$PD_DIR/blocks/$BLOCK"
CORE="$(ls "$BDIR"/*.core 2>/dev/null | head -1 || true)"
[[ -f "$CORE" ]]            || { echo "no .core in $BDIR" >&2; exit 1; }
[[ -f "$BDIR/config.json" ]] || { echo "no config.json in $BDIR" >&2; exit 1; }

# --- 1) Resolve closure with FuseSoC (the sim flow's pinned venv) -------------
source "$DESIGN_DIR/.env.local"
# shellcheck disable=SC1091
source "$FUSESOC_VENV/bin/activate"
VLNV="$(sed -n 's/^name:[[:space:]]*//p' "$CORE" | head -1)"
MUNGED="${VLNV//:/_}"
echo "[harden] FuseSoC resolve: $VLNV"
( cd "$REPO_ROOT" && fusesoc --cores-root "$REPO_ROOT" \
    run --target=lint --setup --tool=verilator "$VLNV" ) >/tmp/${BLOCK}_setup.log 2>&1 \
  || { echo "fusesoc setup failed — see /tmp/${BLOCK}_setup.log"; tail -20 /tmp/${BLOCK}_setup.log; exit 1; }
VCDIR="$REPO_ROOT/build/$MUNGED/lint-verilator"
VC="$VCDIR/$MUNGED.vc"
[[ -f "$VC" ]] || { echo "no .vc at $VC" >&2; exit 1; }
deactivate 2>/dev/null || true

# --- 2) Merge config.json + raw-SV file list -> config.resolved.json ----------
RESOLVED="$BDIR/config.resolved.json"
python3 - "$VC" "$VCDIR" "$BDIR/config.json" "$BLOCK" "$RESOLVED" <<'PY'
import json, os, sys
vc, vcdir, base, block, out = sys.argv[1:6]
bdir = os.path.dirname(base)
# dir:: is LibreLane's own "relative to this config file" prefix -- keeps
# the resolved config portable across checkouts/machines instead of baking
# in this machine's absolute path.
def relpath(p):
    return "dir::" + os.path.relpath(os.path.realpath(p), bdir)
files, incs = [], []
for ln in open(vc):
    ln = ln.strip()
    if ln.startswith("+incdir+"):
        incs.append(relpath(os.path.join(vcdir, ln[len("+incdir+"):])))
    elif ln.endswith(".sv"):
        files.append(relpath(os.path.join(vcdir, ln)))
cfg = json.load(open(base))
# --keep-hierarchy: without it, slang's frontend tries to "inline" (flatten)
# module instance boundaries during its own elaboration pass, before Yosys
# ever sees the design. 
cfg.update({
    "VERILOG_FILES": files,
    "VERILOG_INCLUDE_DIRS": incs,
    "USE_SLANG": True,
    "SLANG_ARGUMENTS": ["--top", block, "--keep-hierarchy"],
})
cfg.setdefault("VERILOG_DEFINES", ["SYNTHESIS=1"])
json.dump(cfg, open(out, "w"), indent=2)
print(f"[harden] {out}: {len(files)} SV files, {len(incs)} incdirs, USE_SLANG=true")
PY

# --- 3) Run LibreLane inside its nix-shell ------------------------------------
echo "[harden] LibreLane (nix-shell @ $LIBRELANE_DIR) PDK=$PDK ${EXTRA:+[$EXTRA]}"
ll_shell "librelane --pdk $PDK --pdk-root $PDK_ROOT --manual-pdk $EXTRA $RESOLVED"
