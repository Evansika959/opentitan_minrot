# Custom PDN for the gf180mcu_ocd_ip_sram__sram256x8m8wm1 macro (21-bank OCD IMEM).
#
# Same starting point as ../tlul_sram_if_macro/pdn_cfg.tcl: LibreLane's default
# macro grid only does add_pdn_connect -grid macro -layers "Metal4 Metal5", but
# this macro's power pins are on Metal1/Metal2/Metal3, so the macro's own rails
# never get a via up to the Metal4 core grid without extra help.
source $::env(SCRIPTS_DIR)/openroad/common/pdn_cfg.tcl

# Bridge the full chain: Metal1->Metal2->Metal3->Metal4. add_pdn_connect only
# allows a via where shapes on both layers already geometrically overlap -- it
# draws no new geometry, so this alone is enough as long as some Metal3 finger
# of a given net actually lands on a Metal4 global-grid crossing somewhere in
# the macro (true for VDD everywhere, and true for VSS too now that
# ../macro_placement.cfg nudges the one problem bank column's third lane by
# 3um so its VSS finger lands on the crossing instead of missing it -- see
# that file's own header comment for the full story of how this was found:
# every same-layer geometry hack tried here first (stripes, rings on
# Metal1/2/3/4) either failed to reconnect VSS or shorted it into VDD, because
# VDD's own finger placement happened to straddle the only available approach
# at the original macro position. The real fix turned out to be moving the
# macro a few um, not adding PDN geometry at all.
add_pdn_connect -grid macro -layers "Metal1 Metal2"
add_pdn_connect -grid macro -layers "Metal2 Metal3"
add_pdn_connect -grid macro -layers "Metal3 Metal4"
