# xbar_tlul_2to4 — block-level timing constraints (OpenSTA-compatible).
#
# Context: an on-chip TL-UL crossbar (2 Ibex host adapters x 4 device adapters:
# ROM, exec-SRAM, data-SRAM, UART). EVERY port connects to other logic in the
# SAME clk_i domain; the block has NO chip-level I/O. So input/output delays here
# model the neighbouring REGISTER stages, not board/off-chip delay. The dominant
# paths are combinational host->device feedthroughs (address decode + response
# mux + TL-UL integrity), which pay BOTH the input and the output budget.

set clk_period 50.0 ;# 20 MHz target — keep in sync with CLOCK_PERIOD in config.json

# --- single synchronous clock -------------------------------------------------
create_clock -name clk_i -period $clk_period [get_ports clk_i]

# --- DFT / static pins --------------------------------------------------------
# scanmode_i is a static scan-mode select: constant in functional operation, so
# it is not a real timing path.
set_false_path -from [get_ports {scanmode_i[*]}]

# all inputs except the clock (plain Tcl list ops — OpenSTA has no
# remove_from_collection)
set clk_input [get_port clk_i]
set clk_indx  [lsearch [all_inputs] $clk_input]
set in_wo_clk [lreplace [all_inputs] $clk_indx $clk_indx ""]
set clocks    [get_clocks clk_i]

# --- on-chip I/O budget -------------------------------------------------------
# Reserve ~15% of the period at each boundary for the neighbour register stage
# (launch clk->Q + a little upstream logic on inputs; downstream logic + setup on
# outputs). A feedthrough host->device path thus reserves ~30%, leaving ~70% of
# the period for the crossbar's own logic.
set io_budget [expr {0.15 * $clk_period}]
set_input_delay  -max $io_budget -clock $clocks $data_inputs
set_input_delay  -min 0.0        -clock $clocks $data_inputs

set_output_delay -max $io_budget -clock $clocks $outputs
set_output_delay -min 0.0        -clock $clocks $outputs

# Realistic on-chip drive/load. Model the driver as a medium buffer (drive-4) —
# what a real net fanning across a block actually sees — not a weakest-drive (x1)
# cell, which produces an artificially slow input slew.
set_driving_cell -lib_cell gf180mcu_fd_sc_mcu7t5v0__buf_4 -pin Z $in_wo_clk
set_load 0.02 [all_outputs]

# --- design-rule + clock realism ---------------------------------------------
set_max_fanout 10 [current_design]
set_max_transition 0.75 [current_design]

set_clock_uncertainty 0.10 $clocks
set_clock_transition 0.15 $clocks
set_timing_derate -early 0.95
set_timing_derate -late 1.05
set_propagated_clock [all_clocks]
