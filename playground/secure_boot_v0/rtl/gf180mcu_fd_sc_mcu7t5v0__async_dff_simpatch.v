// gf180mcu_fd_sc_mcu7t5v0__async_dff_simpatch.v -- extended.
//
// Simulation-only replacement for the GF180MCU standard-cell library's
// async-reset/set-capable DFF cells (dffrnq, dffsnq, dffnrnq, dffnsnq,
// dffrsnq, dffnrsnq) and the plain no-reset DFFs (dffq, dffnq) they're
// commonly paired with in a synthesized netlist -- across ALL
// drive-strength variants the vendor library defines (_1, _2, _4).
//
// Why this exists: the vendor's own behavioral model
// (gf180mcu_fd_sc_mcu7t5v0.v) implements these via a `primitive`/`table`
// (UDP) construct (gf180mcu_fd_sc_mcu7t5v0__udp_n_iq_ff) whose async-reset
// row is level-sensitive (RN/SETN, not clock-edge-sensitive). Confirmed by
// direct isolated test (single dffrnq_1 cell, RN=0 held from time 0, D=1
// held constant): Q reads 1 the entire time reset is asserted -- Verilator
// does not honor that UDP row, so Q just tracks whatever value it powers
// up to (D's value, in that test) regardless of RN. The gate netlist's own
// wiring (RN tied straight to rst_ni, no inversion/gating) and the cell's
// synthesis mapping are both correct -- see gls/tlul_sram_if_macro_solo_gls_tb.sv's
// header for the full trace. This is a Verilator/vendor-model interaction
// limitation, not a netlist or RTL defect -- same category of problem as
// rtl/gf180mcu_ocd_ip_sram__sram256x8m8wm1_simpatch.v (already-established
// project convention: hand-write a behaviorally-correct sim-only stand-in,
// never touch the real GDS/LEF/netlist).
//
// EXTENSION (2026-08-01): the original version of this file only patched
// the _1 (weakest) drive-strength variant of each family. Every family
// also has _2 and _4 variants -- SEPARATE wrapper modules in the vendor
// file, each independently guarded (e.g. `GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_2_V`)
// but ALL instantiating the SAME broken shared `_func`/UDP primitive
// (e.g. gf180mcu_fd_sc_mcu7t5v0__dffrnq_func) -- so the _1-only patch left
// _2/_4 instances just as broken. Root-caused via a real failure: in
// tlul_sram_if_macro_ocd_21bank's fully-hardened netlist, the request
// FIFO gating instruction fetch (u_adapt.u_reqfifo.gen_singleton_fifo's
// full_q) happened to synthesize to dffrnq_2 (not _1), so its "not full"
// (wready/a_ready) reset value never resolved correctly under Verilator --
// permanently withholding a_ready and silently wedging the very first
// instruction fetch after reset, while other tests that only ever
// exercised _1-variant flops (e.g. the standalone macro smoke test) saw
// no symptom at all. Confirmed root cause via cell-driver trace in the
// macro's own netlist (139557: gf180mcu_fd_sc_mcu7t5v0__dffrnq_2 _1654_
// (.D(\u_adapt.u_reqfifo.gen_singleton_fifo.full_d ), ...)) before writing
// this fix.
//
// Guarded with the SAME include-guard macro names the vendor file uses
// per variant (e.g. `GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_2_V`) so that reading
// this file BEFORE gf180mcu_fd_sc_mcu7t5v0.v in a fileset causes the
// vendor file's own `ifndef` to skip its (broken-under-Verilator)
// definition instead of erroring on a duplicate module. Their now-unused
// `_func`/UDP modules still get defined by the vendor file (nothing
// instantiates them anymore) -- harmless, elaborated but unused.
//
// Functional intent per cell family (cross-checked against the project's
// own yosys dfflibmap output mapping each cell to its Yosys internal
// type); identical behavior across all drive-strength variants of a
// family, only the guard/module name changes:
//   dffq_*    ($_DFF_P_)     : posedge CLK,           no reset
//   dffnq_*   ($_DFF_N_)     : negedge CLKN,           no reset
//   dffrnq_*  ($_DFF_PN0_)   : posedge CLK,  async RN   -> reset-to-0
//   dffsnq_*  ($_DFF_PN1_)   : posedge CLK,  async SETN -> set-to-1
//   dffnrnq_* ($_DFF_NN0_)   : negedge CLKN, async RN   -> reset-to-0
//   dffnsnq_* ($_DFF_NN1_)   : negedge CLKN, async SETN -> set-to-1
//   dffrsnq_* ($_DFFSR_PNN_) : posedge CLK,  async RN + async SETN (RN dominates)
//   dffnrsnq_*($_DFFSR_NNN_) : negedge CLKN, async RN + async SETN (RN dominates)
// Port lists for _2/_4 verified identical to _1 (drive-strength-only
// difference) against the vendor file directly.

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffq_1( CLK, D, Q );
  input  CLK, D;
  output reg Q;
  always @(posedge CLK) Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffq_2( CLK, D, Q );
  input  CLK, D;
  output reg Q;
  always @(posedge CLK) Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffq_4( CLK, D, Q );
  input  CLK, D;
  output reg Q;
  always @(posedge CLK) Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffnq_1( CLKN, D, Q );
  input  CLKN, D;
  output reg Q;
  always @(negedge CLKN) Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffnq_2( CLKN, D, Q );
  input  CLKN, D;
  output reg Q;
  always @(negedge CLKN) Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffnq_4( CLKN, D, Q );
  input  CLKN, D;
  output reg Q;
  always @(negedge CLKN) Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffrnq_1( CLK, D, RN, Q );
  input  CLK, D, RN;
  output reg Q;
  always @(posedge CLK or negedge RN)
    if (!RN) Q <= 1'b0;
    else     Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffrnq_2( CLK, D, RN, Q );
  input  CLK, D, RN;
  output reg Q;
  always @(posedge CLK or negedge RN)
    if (!RN) Q <= 1'b0;
    else     Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFRNQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffrnq_4( CLK, D, RN, Q );
  input  CLK, D, RN;
  output reg Q;
  always @(posedge CLK or negedge RN)
    if (!RN) Q <= 1'b0;
    else     Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFSNQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFSNQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffsnq_1( CLK, D, SETN, Q );
  input  CLK, D, SETN;
  output reg Q;
  always @(posedge CLK or negedge SETN)
    if (!SETN) Q <= 1'b1;
    else       Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFSNQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFSNQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffsnq_2( CLK, D, SETN, Q );
  input  CLK, D, SETN;
  output reg Q;
  always @(posedge CLK or negedge SETN)
    if (!SETN) Q <= 1'b1;
    else       Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFSNQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFSNQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffsnq_4( CLK, D, SETN, Q );
  input  CLK, D, SETN;
  output reg Q;
  always @(posedge CLK or negedge SETN)
    if (!SETN) Q <= 1'b1;
    else       Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNRNQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNRNQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffnrnq_1( CLKN, D, RN, Q );
  input  CLKN, D, RN;
  output reg Q;
  always @(negedge CLKN or negedge RN)
    if (!RN) Q <= 1'b0;
    else     Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNRNQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNRNQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffnrnq_2( CLKN, D, RN, Q );
  input  CLKN, D, RN;
  output reg Q;
  always @(negedge CLKN or negedge RN)
    if (!RN) Q <= 1'b0;
    else     Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNRNQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNRNQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffnrnq_4( CLKN, D, RN, Q );
  input  CLKN, D, RN;
  output reg Q;
  always @(negedge CLKN or negedge RN)
    if (!RN) Q <= 1'b0;
    else     Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNSNQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNSNQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffnsnq_1( CLKN, D, SETN, Q );
  input  CLKN, D, SETN;
  output reg Q;
  always @(negedge CLKN or negedge SETN)
    if (!SETN) Q <= 1'b1;
    else       Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNSNQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNSNQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffnsnq_2( CLKN, D, SETN, Q );
  input  CLKN, D, SETN;
  output reg Q;
  always @(negedge CLKN or negedge SETN)
    if (!SETN) Q <= 1'b1;
    else       Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNSNQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNSNQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffnsnq_4( CLKN, D, SETN, Q );
  input  CLKN, D, SETN;
  output reg Q;
  always @(negedge CLKN or negedge SETN)
    if (!SETN) Q <= 1'b1;
    else       Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFRSNQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFRSNQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffrsnq_1( CLK, D, SETN, RN, Q );
  input  CLK, D, SETN, RN;
  output reg Q;
  // RN dominates SETN if both are ever asserted simultaneously (unverified
  // against real silicon for this simultaneous-assert case -- not exercised
  // by any netlist checked so far; flag if it ever matters).
  always @(posedge CLK or negedge RN or negedge SETN)
    if (!RN)        Q <= 1'b0;
    else if (!SETN) Q <= 1'b1;
    else            Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFRSNQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFRSNQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffrsnq_2( CLK, D, SETN, RN, Q );
  input  CLK, D, SETN, RN;
  output reg Q;
  always @(posedge CLK or negedge RN or negedge SETN)
    if (!RN)        Q <= 1'b0;
    else if (!SETN) Q <= 1'b1;
    else            Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFRSNQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFRSNQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffrsnq_4( CLK, D, SETN, RN, Q );
  input  CLK, D, SETN, RN;
  output reg Q;
  always @(posedge CLK or negedge RN or negedge SETN)
    if (!RN)        Q <= 1'b0;
    else if (!SETN) Q <= 1'b1;
    else            Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNRSNQ_1_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNRSNQ_1_V
module gf180mcu_fd_sc_mcu7t5v0__dffnrsnq_1( CLKN, D, SETN, RN, Q );
  input  CLKN, D, SETN, RN;
  output reg Q;
  always @(negedge CLKN or negedge RN or negedge SETN)
    if (!RN)        Q <= 1'b0;
    else if (!SETN) Q <= 1'b1;
    else            Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNRSNQ_2_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNRSNQ_2_V
module gf180mcu_fd_sc_mcu7t5v0__dffnrsnq_2( CLKN, D, SETN, RN, Q );
  input  CLKN, D, SETN, RN;
  output reg Q;
  always @(negedge CLKN or negedge RN or negedge SETN)
    if (!RN)        Q <= 1'b0;
    else if (!SETN) Q <= 1'b1;
    else            Q <= D;
endmodule
`endif

`ifndef GF180MCU_FD_SC_MCU7T5V0__DFFNRSNQ_4_V
`define GF180MCU_FD_SC_MCU7T5V0__DFFNRSNQ_4_V
module gf180mcu_fd_sc_mcu7t5v0__dffnrsnq_4( CLKN, D, SETN, RN, Q );
  input  CLKN, D, SETN, RN;
  output reg Q;
  always @(negedge CLKN or negedge RN or negedge SETN)
    if (!RN)        Q <= 1'b0;
    else if (!SETN) Q <= 1'b1;
    else            Q <= D;
endmodule
`endif
