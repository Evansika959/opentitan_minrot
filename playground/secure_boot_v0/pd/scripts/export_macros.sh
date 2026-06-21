#!/usr/bin/env bash
# Export hardened-block deliverables (the "finished macros") for SoC/PD-top integration.
#
# For each block that has a COMPLETED run (a final/ with a GDS), copies the macro
# views into pd/macros/<block>/ and writes pd/macros/macros.json -- a MACROS-dict
# manifest (DESIGN_NAME -> gds/lef/lib{corner}/spice/nl, absolute paths) ready to
# drop into a top-level LibreLane config.
#
# Usage: export_macros.sh [block ...]   (no args = every block with a finished run)
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh" >/dev/null 2>&1

OUT="$PD_DIR/macros"
mkdir -p "$OUT"

if [[ $# -gt 0 ]]; then
  BLOCKS=("$@")
else
  mapfile -t BLOCKS < <(for d in "$PD_DIR"/blocks/*/; do basename "$d"; done)
fi

EXPORTED=()
for BLK in "${BLOCKS[@]}"; do
  BDIR="$PD_DIR/blocks/$BLK"
  [[ -f "$BDIR/config.json" ]] || { echo "  ! $BLK: no config.json, skipping"; continue; }

  # newest run that actually finished (has final/gds)
  RUN=""
  for r in $(ls -dt "$BDIR"/runs/*/ 2>/dev/null); do
    [[ -d "${r}final/gds" ]] && { RUN="$r"; break; }
  done
  [[ -n "$RUN" ]] || { echo "  ! $BLK: no completed run (no final/gds), skipping"; continue; }

  FINAL="${RUN}final"
  D="$OUT/$BLK"; rm -rf "$D"; mkdir -p "$D"

  # core views -> flat under macros/<block>/ (lib + spef corners flattened in)
  cp -f "$FINAL"/gds/*.gds     "$D/" 2>/dev/null || true
  cp -f "$FINAL"/lef/*.lef     "$D/" 2>/dev/null || true
  cp -f "$FINAL"/def/*.def     "$D/" 2>/dev/null || true
  cp -f "$FINAL"/nl/*.nl.v     "$D/" 2>/dev/null || true
  cp -f "$FINAL"/pnl/*.pnl.v   "$D/" 2>/dev/null || true
  cp -f "$FINAL"/spice/*.spice "$D/" 2>/dev/null || true
  cp -f "$FINAL"/sdc/*.sdc     "$D/" 2>/dev/null || true
  find "$FINAL/lib"  -name '*.lib'  -exec cp -f {} "$D/" \; 2>/dev/null || true
  find "$FINAL/spef" -name '*.spef' -exec cp -f {} "$D/" \; 2>/dev/null || true

  echo "  + $BLK <- $(basename "$RUN")  ($(ls "$D" | wc -l) views)"
  EXPORTED+=("$BLK")
done

# ---- build macros.json (MACROS-dict manifest) -------------------------------
python3 - "$OUT" "${EXPORTED[@]}" <<'PY'
import json, os, sys, glob, re
out = sys.argv[1]; blocks = sys.argv[2:]
macros = {}
for blk in blocks:
    d = os.path.join(out, blk)
    cfg = json.load(open(os.path.join(os.path.dirname(out), "blocks", blk, "config.json")))
    name = cfg["DESIGN_NAME"]
    def one(pat):
        g = sorted(glob.glob(os.path.join(d, pat)))
        return g[0] if g else None
    libs = {}
    for lib in sorted(glob.glob(os.path.join(d, "*.lib"))):
        m = re.search(r"__([a-z]{2}_.*?)\.lib$", os.path.basename(lib))
        corner = m.group(1) if m else "nom_tt_025C_5v00"
        libs.setdefault(corner, []).append(lib)
    entry = {}
    if one("*.gds"):    entry["gds"]   = [one("*.gds")]
    if one("*.lef"):    entry["lef"]   = [one("*.lef")]
    if libs:            entry["lib"]   = libs
    if one("*.spice"):  entry["spice"] = [one("*.spice")]
    if one("*.nl.v"):   entry["nl"]    = [one("*.nl.v")]
    macros[name] = entry
json.dump(macros, open(os.path.join(out, "macros.json"), "w"), indent=2)
print(f"\n  macros.json: {len(macros)} macro(s) -> {', '.join(macros)}")
PY
echo "  done -> $OUT"
