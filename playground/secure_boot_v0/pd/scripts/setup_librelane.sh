#!/usr/bin/env bash
# One-time: clone LibreLane (pinned tag) and validate it via its own nix-shell.
# This is the install method the LibreLane project recommends. The clone is used
# AS-IS — no vendor software is modified.
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"

if [[ ! -d "$LIBRELANE_DIR/.git" ]]; then
  echo "[setup] cloning LibreLane $LIBRELANE_TAG -> $LIBRELANE_DIR"
  mkdir -p "$(dirname "$LIBRELANE_DIR")"
  git clone https://github.com/librelane/librelane "$LIBRELANE_DIR"
  git -C "$LIBRELANE_DIR" -c advice.detachedHead=false checkout "$LIBRELANE_TAG"
else
  echo "[setup] LibreLane present at $LIBRELANE_DIR ($(git -C "$LIBRELANE_DIR" describe --tags --always 2>/dev/null))"
fi

echo "[setup] entering nix-shell and running smoke test (first time builds/downloads the env)…"
ll_shell "librelane --smoke-test"
echo "[setup] OK — environment validated."
