# Custom PDN for top_pd_puf.
#
# Same root cause and fix as ../tlul_sram_if_macro/pdn_cfg.tcl: LibreLane's
# default macro grid only does add_pdn_connect -grid macro -layers "Metal4
# Metal5", but the PUF's own foundry SRAM primitive
# (gf180mcu_fd_ip_sram__sram64x8m8wm1, blackboxed directly here since it's
# real, already-signed-off foundry IP, not a pre-hardened sub-block) exposes
# its power pins on Metal2/Metal3 natively -- so without this bridge, its
# rails never reach the Metal4 core grid (PSM-0039/PSM-0069, unconnected VSS).
#
# The other two real macros at this level (tlul_sram_if_macro_ocd_21bank and
# tlul_sram_if_macro) are pre-hardened sub-blocks, not raw foundry macros --
# confirmed via their own exported LEF that their external VDD/VSS pins are
# already on Metal4/Metal5, matching the default grid's own assumption, so
# this extra connect permission is a safe no-op for them (no Metal3 pin shape
# exists on their exported interface to match against).
source $::env(SCRIPTS_DIR)/openroad/common/pdn_cfg.tcl

# Only bridge the macro's own top pin layer (Metal3) to the core vertical
# strap layer (Metal4) -- do NOT add a Metal2<->Metal3 connect, the macro
# already ties those together internally (same reasoning as the sibling
# block's script: adding it drops a redundant via array and produces tens of
# thousands of DRC violations).
add_pdn_connect -grid macro -layers "Metal3 Metal4"
