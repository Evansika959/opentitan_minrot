# Custom top-level PDN.
#
# Our hardened blocks expose power on BOTH Metal4 and Metal5 (their block-PDN
# vertical+horizontal mesh). So we connect them via Metal5 -- NO extra Metal4
# stripes over macros (those overlapped the blocks' own Metal4 at illegal spacing
# -> 2868 KLayout DRC). Dense Metal5 stripes over each macro merge with the block's
# Metal5 power and tie into the top Metal5 horizontal grid; the base config's
# `add_pdn_connect -grid macro -layers "Metal4 Metal5"` vias these down to the
# blocks' Metal4 as well. A larger halo keeps the stdcell Metal4 straps off the
# macros so they don't orphan.
source $::env(SCRIPTS_DIR)/openroad/common/pdn_cfg.tcl

add_pdn_stripe \
    -grid macro \
    -layer Metal5 \
    -width 1.6 \
    -spacing 1.7 \
    -pitch 80 \
    -offset 40 \
    -starts_with POWER
