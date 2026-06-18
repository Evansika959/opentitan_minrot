#!/usr/bin/env bash
# Shared env for the secure_boot_v0 LibreLane flow.
#
# We use the method the LibreLane project documents: a local *clone* of the
# LibreLane repo entered via `nix-shell`, which provides librelane + all EDA tools
# (yosys-with-plugins incl. slang, openroad, klayout, magic) at pinned versions.
#
# Source this to load the vars + helpers (ll_shell, ll_env). Running it directly
# (`bash scripts/env.sh`) just prints the resolved environment summary.
# (No `set -e` — it would leak to callers when sourced.)

PD_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DESIGN_DIR="$(cd "$PD_DIR/.." && pwd)"                 # playground/secure_boot_v0
REPO_ROOT="$(cd "$DESIGN_DIR" && git rev-parse --show-toplevel)"
HW="$REPO_ROOT/hw"
export PD_DIR DESIGN_DIR REPO_ROOT HW

# Local LibreLane checkout (created by setup_librelane.sh) + pinned release tag.
# Kept OUTSIDE this repo (alongside the RISC-V toolchain in ~/tools) so no vendor
# software is copied into the project. Override LIBRELANE_DIR to relocate.
LIBRELANE_DIR="${LIBRELANE_DIR:-$HOME/tools/librelane}"
LIBRELANE_TAG="${LIBRELANE_TAG:-3.0.4}"

# PDK: the wafer.space gf180mcu shuttle distribution (what chipathon-2026 targets),
# cloned locally by setup_pdk.sh and used via `librelane --manual-pdk` (NOT ciel).
# PDK_ROOT is the clone root; the variant lives at $PDK_ROOT/$PDK.
PDK="${PDK:-gf180mcuD}"
PDK_TAG="${PDK_TAG:-1.8.0}"
PDK_ROOT="${PDK_ROOT:-$PD_DIR/pdk/gf180mcu}"
export LIBRELANE_DIR LIBRELANE_TAG PDK PDK_TAG PDK_ROOT

# Run a command string inside the LibreLane nix-shell (the recommended entrypoint).
# All paths used here are space-free, so no extra quoting is needed.
ll_shell() {
  [[ -e "$LIBRELANE_DIR/shell.nix" || -e "$LIBRELANE_DIR/default.nix" ]] \
    || { echo "LibreLane clone not found at $LIBRELANE_DIR — run ./scripts/setup_librelane.sh" >&2; return 1; }
  nix-shell "$LIBRELANE_DIR" --run "$1"
}

# Print a one-screen summary of the resolved environment (paths + tool status).
ll_env() {
  local clone="missing" pdk="missing"
  if [[ -e "$LIBRELANE_DIR/shell.nix" || -e "$LIBRELANE_DIR/default.nix" ]]; then
    clone="present ($(git -C "$LIBRELANE_DIR" describe --tags --always 2>/dev/null || echo '?'))"
  fi
  [[ -d "$PDK_ROOT/$PDK/libs.ref" ]] && pdk="present"
  printf '%s\n' \
    "secure_boot_v0 LibreLane flow — environment" \
    "  REPO_ROOT     : $REPO_ROOT" \
    "  PD_DIR        : $PD_DIR" \
    "  LIBRELANE_DIR : $LIBRELANE_DIR  [$clone]" \
    "  LIBRELANE_TAG : $LIBRELANE_TAG" \
    "  PDK / tag     : $PDK / $PDK_TAG (wafer.space, --manual-pdk)" \
    "  PDK_ROOT      : $PDK_ROOT  [$pdk]" \
    "  nix           : $(command -v nix >/dev/null 2>&1 && nix --version 2>/dev/null || echo 'not found')"
}

# When executed directly (not sourced), print the summary instead of doing nothing.
if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
  ll_env
fi
