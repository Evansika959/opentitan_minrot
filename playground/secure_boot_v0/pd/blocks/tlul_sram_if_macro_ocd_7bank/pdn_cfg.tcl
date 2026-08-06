# Custom PDN for the gf180mcu_ocd_ip_sram__sram256x8m8wm1 macro (7-bank OCD IMEM (naive 3-stage boot area experiment)).
#
# ROOT CAUSE FOUND (2026-08-04, confirmed on the 2-bank bisection testbed):
# the OCD macro's own VDD/VSS pins already span Metal1/Metal2/Metal3
# internally (VDD: Metal2+Metal3, VSS: Metal1+Metal2+Metal3+Nwell --
# confirmed directly from the macro's LEF PIN geometry). The previous
# version of this file issued THREE add_pdn_connect calls (Metal1-Metal2,
# Metal2-Metal3, Metal3-Metal4), and the first two are pure redundant
# duplicates on top of connections the macro already makes internally --
# OpenROAD drops a SEPARATE, independent via array at each redundant
# connect layer pair, landing multiple overlapping via arrays on the same
# already-tied-together pins. Confirmed via direct GDS polygon inspection
# on the 2-bank testbed: what looked like "one via with touching/merged
# cuts" was actually two independently-placed, correctly-formed via arrays
# physically overlapping each other by ~0.04um at each interleave point --
# not a cut-generation defect (OpenROAD's own via master geometry is always
# correctly spaced at 0.26um gaps, verified directly). The sibling
# tlul_sram_if_macro block (FD-family macro, same underlying issue)
# already documented and fixed this exact mechanism for its own macro --
# this file was just never updated to match when the OCD-family macro was
# swapped in. Fixing the 2-bank block's pdn_cfg.tcl to only bridge Metal3
# to Metal4 (dropping the redundant Metal1-Metal2/Metal2-Metal3 connects)
# took KLayout DRC errors from 54164 to a clean pass. Applying the same fix
# here.
#
# The VSS macro-placement nudge below (../macro_placement.cfg's -3um X
# offset on one bank column's third lane) is UNRELATED to the redundant-via
# bug and still applies: it's what makes VSS's Metal3 finger land on a
# Metal4 global-grid crossing in the first place, which this single
# Metal3-Metal4 connect still needs.
source $::env(SCRIPTS_DIR)/openroad/common/pdn_cfg.tcl
add_pdn_connect -grid macro -layers "Metal3 Metal4"
