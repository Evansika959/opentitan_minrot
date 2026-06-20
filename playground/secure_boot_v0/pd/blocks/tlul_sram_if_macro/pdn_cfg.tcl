# Custom PDN for the gf180 SRAM macro block.
#
# LibreLane's default macro grid only does:  add_pdn_connect -grid macro -layers "Metal4 Metal5"
# but the gf180mcu_fd_ip_sram power pins are on Metal2/Metal3, so the macro power
# rings never bridge up to the Metal4/Metal5 core grid -> PSM-0069 (unconnected
# VDD on Metal2). We reuse the stock PDN verbatim, then add the missing via stack
# from the macro pin layers up to the core vertical layer (Metal4).
source $::env(SCRIPTS_DIR)/openroad/common/pdn_cfg.tcl

# The macro already ties its Metal2 and Metal3 power pins together internally,
# so we ONLY bridge its top pin layer (Metal3) to the core vertical strap layer
# (Metal4). Adding a Metal2<->Metal3 connect here drops a redundant Via2 array
# onto the macro pins and produces tens of thousands of Via2 DRC violations.
add_pdn_connect -grid macro -layers "Metal3 Metal4"
