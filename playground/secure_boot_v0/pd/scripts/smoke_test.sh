#!/usr/bin/env bash
# Run the LibreLane smoke test inside the cloned-repo nix-shell.
# (setup_librelane.sh also runs this; kept as a standalone convenience.)
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/env.sh"
echo "[smoke] LibreLane dir : $LIBRELANE_DIR"
echo "[smoke] PDK_ROOT      : $PDK_ROOT"
ll_shell "librelane --smoke-test"
echo "[smoke] OK"
