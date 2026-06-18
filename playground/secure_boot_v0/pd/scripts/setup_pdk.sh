#!/usr/bin/env bash
# One-time: clone the wafer.space gf180mcu PDK (the shuttle-qualified distribution
# that chipathon-2026 targets), pinned to a tag, for use via `librelane --manual-pdk`.
# Mirrors `make clone-pdk` from github.com/Mauricio-xx/chipathon-2026-gf180mcu-padring
#   (git clone https://github.com/wafer-space/gf180mcu.git ... --branch <PDK_TAG>).
# The clone is used as-is — no vendor software is modified.
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"

if [[ ! -d "$PDK_ROOT/.git" ]]; then
  echo "[setup_pdk] cloning wafer-space/gf180mcu @ $PDK_TAG -> $PDK_ROOT"
  mkdir -p "$(dirname "$PDK_ROOT")"
  git clone https://github.com/wafer-space/gf180mcu.git "$PDK_ROOT" --depth 1 --branch "$PDK_TAG"
else
  echo "[setup_pdk] PDK clone present at $PDK_ROOT ($(git -C "$PDK_ROOT" describe --tags --always 2>/dev/null))"
fi

if [[ -d "$PDK_ROOT/$PDK/libs.ref" ]]; then
  echo "[setup_pdk] OK — $PDK at $PDK_ROOT/$PDK"
  echo "[setup_pdk] libs.ref: $(ls "$PDK_ROOT/$PDK/libs.ref" 2>/dev/null | tr '\n' ' ')"
  echo "[setup_pdk] use: librelane --pdk $PDK --pdk-root $PDK_ROOT --manual-pdk <config>  (harden_block.sh does this)"
else
  echo "[setup_pdk] ERROR: $PDK_ROOT/$PDK/libs.ref not found — check the clone layout / PDK_TAG" >&2
  exit 1
fi
