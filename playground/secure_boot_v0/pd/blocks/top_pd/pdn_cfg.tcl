# Per-instance macro PDN grid (the wafer.space gf180mcu-template method, scaled to
# our six hardened blocks).
#
# Why: every block was hardened with the default gf180 PDN, so they all expose the
# SAME power-pin geometry, relative to each block's own origin:
#   Metal4 (vertical):   VDD center 23.04 / VSS 26.34, pitch 153.6, width 1.6
#   Metal5 (horizontal): VDD center 32.33 / VSS 35.63, pitch 153.18, width 1.6
# The block pin pitch (153.6) equals the top grid pitch, but the blocks are placed
# at coords like x=1400 (1400/153.6 = 9.11, not integer), so their pins land ~17um
# off the top straps -> the M4<->M5 via never forms -> orphaned VDD/VSS fragments.
#
# Fix: a macro grid whose stripes sit EXACTLY on each block's pins (offset relative
# to the macro origin = block origin, so it self-aligns regardless of placement).
# Same net -> the stripe merges with the block pin (no DRC), and being on the macro
# grid it gets the M4<->M5 via into the top grid. This replaces the orphaned top
# stdcell straps over each macro with connected, aligned ones.
source $::env(SCRIPTS_DIR)/openroad/common/pdn_cfg.tcl

define_pdn_grid -macro \
    -instances "u_ibex u_imem u_esram u_dmem u_xbar u_uart" \
    -name macro_aligned \
    -starts_with POWER \
    -halo "$::env(PDN_HORIZONTAL_HALO) $::env(PDN_VERTICAL_HALO)"

# Stripes aligned to each block's own M4/M5 power pins (offset = block-origin-
# relative pin center; same-net merge, so no spacing DRC).
add_pdn_stripe -grid macro_aligned -layer Metal4 \
    -width 1.6 -spacing 1.7 -pitch 153.6  -offset 23.04 -starts_with POWER
add_pdn_stripe -grid macro_aligned -layer Metal5 \
    -width 1.6 -spacing 1.7 -pitch 153.18 -offset 32.33 -starts_with POWER

# Via the aligned M4/M5 up into the top Metal5 grid.
add_pdn_connect -grid macro_aligned -layers "Metal4 Metal5"
