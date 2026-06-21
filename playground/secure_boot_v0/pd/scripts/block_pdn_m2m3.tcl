# Custom in-block PDN: M1 rails -> sparse M2 risers -> M3 (H), exposing M3.
# M4 and M5 are left ENTIRELY FREE (no power, no signal -- routing is capped at
# Metal3 via RT_MAX_LAYER) so the chip-top owns M4/M5 outright.
# ---------------------------------------------------------------------------
# Shared by all std-cell blocks. Referenced from each block's config.json:
#     "PDN_CFG": "dir::../../scripts/block_pdn_m2m3.tcl"
#     "RT_MAX_LAYER": "Metal3"     <-- REQUIRED: keeps M4/M5 empty of signals.
#
# WHY this is the clean hierarchical split: block owns M1/M2/M3, top owns M4/M5,
# and the ONLY handoff is top-M4 <-> block-M3 (Via3). No layer is shared between
# block and top, so there is zero duplicate-metal risk at integration (the M4.2a /
# Via4 "2868 DRC" came from block+top both using M4).
#
# WHY no rail shadowing: the connect chain M1->M2->M3 is all ADJACENT and
# PERPENDICULAR (M1 H rail -> M2 V riser -> M3 H strap), so no via stack ever
# climbs through a layer that carries opposite-net straps. (The plain M3/M4 scheme
# failed PDN-0179 precisely because M1->M4 had to cross M3.)
#
# M2 is kept SPARSE (RISER_PITCH): with only M2+M3 available for signal, M2 must
# stay mostly open for routing. The earlier 461-Metal2-DRC blow-up used M2 as a
# DENSE main PDN layer (153.6 pitch) AND let signals spill to M4/M5; here M3 + M1
# rails carry the power and M2 is just a coarse vertical tie.

source $::env(SCRIPTS_DIR)/openroad/common/io.tcl
source $::env(SCRIPTS_DIR)/openroad/common/set_global_connections.tcl
set_global_connections

# --- secondary power nets + voltage domain (verbatim from the stock flow) -----
set secondary []
foreach vdd $::env(VDD_NETS) gnd $::env(GND_NETS) {
    if { $vdd != $::env(VDD_NET)} {
        lappend secondary $vdd
        set db_net [[ord::get_db_block] findNet $vdd]
        if {$db_net == "NULL"} {
            set net [odb::dbNet_create [ord::get_db_block] $vdd]
            $net setSpecial
            $net setSigType "POWER"
        }
    }
    if { $gnd != $::env(GND_NET)} {
        lappend secondary $gnd
        set db_net [[ord::get_db_block] findNet $gnd]
        if {$db_net == "NULL"} {
            set net [odb::dbNet_create [ord::get_db_block] $gnd]
            $net setSpecial
            $net setSigType "GROUND"
        }
    }
}
set_voltage_domain -name CORE -power $::env(VDD_NET) -ground $::env(GND_NET) \
    -secondary_power $secondary

# --- tunables ----------------------------------------------------------------
set RISER_PITCH 307.2   ;# M2 vertical riser pitch (2x the 153.6 mesh -> sparse, keeps M2 open for signal)
set STRAP_W     1.6
set STRAP_SP    1.7
set MESH_HPITCH 153.18  ;# M3 horizontal pitch (main power distribution + exposed pin)

# --- grid: expose ONLY Metal3 as the macro power pins ------------------------
define_pdn_grid \
    -name stdcell_grid \
    -starts_with POWER \
    -voltage_domain CORE \
    -pins "Metal3"

# M3 horizontal mesh (the layer the chip-top vias down onto, top-M4 <-> block-M3)
add_pdn_stripe -grid stdcell_grid -layer Metal3 \
    -width $STRAP_W -spacing $STRAP_SP -pitch $MESH_HPITCH -offset $::env(PDN_HOFFSET) \
    -starts_with POWER

# M2 sparse vertical risers (tie M1 rails up to M3; below M3 so no shadowing)
add_pdn_stripe -grid stdcell_grid -layer Metal2 \
    -width $STRAP_W -spacing $STRAP_SP -pitch $RISER_PITCH -offset $::env(PDN_VOFFSET) \
    -starts_with POWER

# M1 std-cell rails (cell power), followpins
add_pdn_stripe -grid stdcell_grid -layer $::env(PDN_RAIL_LAYER) \
    -width $::env(PDN_RAIL_WIDTH) -followpins -starts_with POWER

# --- connect stepwise: every pair adjacent + perpendicular (no shadowing) -----
add_pdn_connect -grid stdcell_grid -layers "$::env(PDN_RAIL_LAYER) Metal2"
add_pdn_connect -grid stdcell_grid -layers "Metal2 Metal3"
