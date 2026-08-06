module miter (
  input  [  0:0] \__pi_clk_i ,
  input  [  3:0] \__pi_en_ifetch_i ,
  input  [  0:0] \__pi_rst_ni ,
  input  [113:0] \__pi_tl_i ,
`ifdef DIRECT_CROSS_POINTS
`else
`endif
  output [ 65:0] \__po_tl_o__gold ,
  output [ 65:0] \__po_tl_o__gate
);
  \gold.tlul_sram_if_macro gold (
    .\__pi_clk_i (\__pi_clk_i ),
    .\__pi_en_ifetch_i (\__pi_en_ifetch_i ),
    .\__pi_rst_ni (\__pi_rst_ni ),
    .\__pi_tl_i (\__pi_tl_i ),
`ifdef DIRECT_CROSS_POINTS
`else
`endif
    .\__po_tl_o (\__po_tl_o__gold )
  );
  \gate.tlul_sram_if_macro gate (
    .\__pi_clk_i (\__pi_clk_i ),
    .\__pi_en_ifetch_i (\__pi_en_ifetch_i ),
    .\__pi_rst_ni (\__pi_rst_ni ),
    .\__pi_tl_i (\__pi_tl_i ),
`ifdef DIRECT_CROSS_POINTS
`else
`endif
    .\__po_tl_o (\__po_tl_o__gate )
  );
`ifdef ASSUME_DEFINED_INPUTS
  miter_def_prop #(1, "assume") \__pi_clk_i__assume (\__pi_clk_i );
  miter_def_prop #(4, "assume") \__pi_en_ifetch_i__assume (\__pi_en_ifetch_i );
  miter_def_prop #(1, "assume") \__pi_rst_ni__assume (\__pi_rst_ni );
  miter_def_prop #(114, "assume") \__pi_tl_i__assume (\__pi_tl_i );
`endif
`ifndef DIRECT_CROSS_POINTS
`endif
`ifdef CHECK_MATCH_POINTS
`endif
`ifdef CHECK_OUTPUTS
  miter_cmp_prop #(66, "assert") \__po_tl_o__assert (\__po_tl_o__gold , \__po_tl_o__gate );
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
  miter_def_prop #(66, "cover") \__po_tl_o__gold_cover (\__po_tl_o__gold );
`endif
`ifdef COVER_DEF_GATE_OUTPUTS
  miter_def_prop #(66, "cover") \__po_tl_o__gate_cover (\__po_tl_o__gate );
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
module \gold.tlul_sram_if_macro (
  input  [  0:0] \__pi_clk_i ,
  input  [  3:0] \__pi_en_ifetch_i ,
  input  [  0:0] \__pi_rst_ni ,
  input  [113:0] \__pi_tl_i ,
  output [ 65:0] \__po_tl_o
);
endmodule
module \gate.tlul_sram_if_macro (
  input  [  0:0] \__pi_clk_i ,
  input  [  3:0] \__pi_en_ifetch_i ,
  input  [  0:0] \__pi_rst_ni ,
  input  [113:0] \__pi_tl_i ,
  output [ 65:0] \__po_tl_o
);
endmodule
