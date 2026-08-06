module miter (
  input  [  5:0] \__pi_A ,
  input  [  0:0] \__pi_CEN ,
  input  [  0:0] \__pi_CLK ,
  input  [  7:0] \__pi_D ,
  input  [  0:0] \__pi_GWEN ,
  input  [  7:0] \__pi_WEN ,
`ifdef DIRECT_CROSS_POINTS
`else
`endif
  output [  7:0] \__po_Q__gold ,
  output [  7:0] \__po_Q__gate
);
  \gold.gf180mcu_fd_ip_sram__sram64x8m8wm1 gold (
    .\__pi_A (\__pi_A ),
    .\__pi_CEN (\__pi_CEN ),
    .\__pi_CLK (\__pi_CLK ),
    .\__pi_D (\__pi_D ),
    .\__pi_GWEN (\__pi_GWEN ),
    .\__pi_WEN (\__pi_WEN ),
`ifdef DIRECT_CROSS_POINTS
`else
`endif
    .\__po_Q (\__po_Q__gold )
  );
  \gate.gf180mcu_fd_ip_sram__sram64x8m8wm1 gate (
    .\__pi_A (\__pi_A ),
    .\__pi_CEN (\__pi_CEN ),
    .\__pi_CLK (\__pi_CLK ),
    .\__pi_D (\__pi_D ),
    .\__pi_GWEN (\__pi_GWEN ),
    .\__pi_WEN (\__pi_WEN ),
`ifdef DIRECT_CROSS_POINTS
`else
`endif
    .\__po_Q (\__po_Q__gate )
  );
`ifdef ASSUME_DEFINED_INPUTS
  miter_def_prop #(6, "assume") \__pi_A__assume (\__pi_A );
  miter_def_prop #(1, "assume") \__pi_CEN__assume (\__pi_CEN );
  miter_def_prop #(1, "assume") \__pi_CLK__assume (\__pi_CLK );
  miter_def_prop #(8, "assume") \__pi_D__assume (\__pi_D );
  miter_def_prop #(1, "assume") \__pi_GWEN__assume (\__pi_GWEN );
  miter_def_prop #(8, "assume") \__pi_WEN__assume (\__pi_WEN );
`endif
`ifndef DIRECT_CROSS_POINTS
`endif
`ifdef CHECK_MATCH_POINTS
`endif
`ifdef CHECK_OUTPUTS
  miter_cmp_prop #(8, "assert") \__po_Q__assert (\__po_Q__gold , \__po_Q__gate );
`endif
`ifdef COVER_DEF_CROSS_POINTS
  `ifdef DIRECT_CROSS_POINTS
  `else
  `endif
`endif
`ifdef COVER_DEF_GOLD_MATCH_POINTS
`endif
`ifdef COVER_DEF_GATE_MATCH_POINTS
`endif
`ifdef COVER_DEF_GOLD_OUTPUTS
  miter_def_prop #(8, "cover") \__po_Q__gold_cover (\__po_Q__gold );
`endif
`ifdef COVER_DEF_GATE_OUTPUTS
  miter_def_prop #(8, "cover") \__po_Q__gate_cover (\__po_Q__gate );
`endif
endmodule
module miter_cmp_prop #(parameter WIDTH=1, parameter TYPE="assert") (input [WIDTH-1:0] in_gold, in_gate);
  reg okay;
  integer i;
  always @* begin
    okay = 1;
    for (i = 0; i < WIDTH; i = i+1)
      okay = okay && (in_gold[i] === 1'bx || in_gold[i] === in_gate[i]);
  end
  generate
    if (TYPE == "assert") always @* assert(okay);
    if (TYPE == "assume") always @* assume(okay);
    if (TYPE == "cover")  always @* cover(okay);
  endgenerate
endmodule
module miter_def_prop #(parameter WIDTH=1, parameter TYPE="assert") (input [WIDTH-1:0] in);
  wire okay = ^in !== 1'bx;
  generate
    if (TYPE == "assert") always @* assert(okay);
    if (TYPE == "assume") always @* assume(okay);
    if (TYPE == "cover")  always @* cover(okay);
  endgenerate
endmodule
module \gold.gf180mcu_fd_ip_sram__sram64x8m8wm1 (
  input  [  5:0] \__pi_A ,
  input  [  0:0] \__pi_CEN ,
  input  [  0:0] \__pi_CLK ,
  input  [  7:0] \__pi_D ,
  input  [  0:0] \__pi_GWEN ,
  input  [  7:0] \__pi_WEN ,
  output [  7:0] \__po_Q
);
endmodule
module \gate.gf180mcu_fd_ip_sram__sram64x8m8wm1 (
  input  [  5:0] \__pi_A ,
  input  [  0:0] \__pi_CEN ,
  input  [  0:0] \__pi_CLK ,
  input  [  7:0] \__pi_D ,
  input  [  0:0] \__pi_GWEN ,
  input  [  7:0] \__pi_WEN ,
  output [  7:0] \__po_Q
);
endmodule
