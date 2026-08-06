# Custom PDN for the gf180 OCD SRAM macro block.
#
# ROOT CAUSE FOUND (2026-08-04): the OCD macro's own VDD/VSS pins already
# span Metal1/Metal2/Metal3 internally (VDD: Metal2+Metal3, VSS:
# Metal1+Metal2+Metal3+Nwell -- confirmed directly from the macro's LEF PIN
# geometry). The previous version of this file issued THREE add_pdn_connect
# calls (Metal1-Metal2, Metal2-Metal3, Metal3-Metal4), and the first two are
# pure redundant duplicates on top of connections the macro already makes
# internally -- OpenROAD drops a SEPARATE, independent via array at each
# redundant connect layer pair, landing multiple overlapping via arrays on
# the same already-tied-together pins. Confirmed via direct GDS polygon
# inspection: what looked like "one via with touching/merged cuts" was
# actually two independently-placed, correctly-formed via arrays physically
# overlapping each other by ~0.04um at each interleave point -- exactly the
# signature of this redundant-connect bug, not a cut-generation defect
# (verified 3x that OpenROAD's own via master geometry is always correctly
# spaced at 0.26um gaps). The sibling tlul_sram_if_macro block (FD-family
# macro, same underlying issue) already documents and fixes this exact
# mechanism for its own macro -- this file was just never updated to match
# when the OCD-family macro was swapped in. Only bridging the macro's
# topmost pin layer (Metal3) up to the core grid's vertical strap layer
# (Metal4), same as the proven-working sibling block.
source $::env(SCRIPTS_DIR)/openroad/common/pdn_cfg.tcl
add_pdn_connect -grid macro -layers "Metal3 Metal4"
