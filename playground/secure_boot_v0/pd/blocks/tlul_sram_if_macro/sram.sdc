# sram_1k — block-level timing constraints (gf180mcuD, OpenSTA-compatible).
# Single synchronous clock (clk_i) shared by the tlul_adapter_sram logic and the
# four sram256x8 macros (macro CLK = clk_i). Macro internal arcs come from its
# .lib; here we only constrain the clock and the block boundary.

set clk_period 100.0 ;# 10 MHz target — keep in sync with CLOCK_PERIOD in config.json

create_clock -name clk_i -period $clk_period [get_ports clk_i]

# all inputs except the clock (plain Tcl list ops; OpenSTA has no remove_from_collection)
set clk_input [get_port clk_i]
set clk_indx  [lsearch [all_inputs] $clk_input]
set in_wo_clk [lreplace [all_inputs] $clk_indx $clk_indx ""]
set clocks    [get_clocks clk_i]

# On-chip I/O budget: ~20% of the period per boundary.
set io_budget [expr {0.20 * $clk_period}]
set_input_delay  $io_budget -clock $clocks $in_wo_clk
set_output_delay $io_budget -clock $clocks [all_outputs]

# Realistic on-chip driver/load.
set_driving_cell -lib_cell gf180mcu_fd_sc_mcu7t5v0__buf_4 -pin Z $in_wo_clk
set_load 0.02 [all_outputs]

# Design-rule + clock realism.
set_max_fanout 16 [current_design]
set_max_transition 3.0 [current_design]
set_clock_uncertainty 0.15 $clocks
set_clock_transition 0.15 $clocks
set_timing_derate -early 0.95
set_timing_derate -late 1.05
set_propagated_clock [all_clocks]
