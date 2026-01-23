// Tiny TL-UL crossbar: 1 host -> 2 devices (single outstanding)
module tlul_xbar_1to2 #(
  parameter logic [31:0] DEV0_BASE = 32'h1000_0000,
  parameter logic [31:0] DEV0_MASK = 32'hFFFF_0000,
  parameter logic [31:0] DEV1_BASE = 32'h2000_0000,
  parameter logic [31:0] DEV1_MASK = 32'hFFFF_F000
) (
  input  logic clk_i,
  input  logic rst_ni,

  input  tlul_pkg::tl_h2d_t h2d_i,
  output tlul_pkg::tl_d2h_t d2h_o,

  output tlul_pkg::tl_h2d_t h2d_dev0_o,
  input  tlul_pkg::tl_d2h_t d2h_dev0_i,

  output tlul_pkg::tl_h2d_t h2d_dev1_o,
  input  tlul_pkg::tl_d2h_t d2h_dev1_i
);
  import tlul_pkg::*;

  typedef enum logic {SEL0=1'b0, SEL1=1'b1} sel_e;
  sel_e sel_d, sel_q;
  logic outstanding_q;

  function automatic logic hit0(input logic [31:0] a);
    return ((a & DEV0_MASK) == DEV0_BASE);
  endfunction
  function automatic logic hit1(input logic [31:0] a);
    return ((a & DEV1_MASK) == DEV1_BASE);
  endfunction

  always_comb begin
    sel_d = SEL0;
    if (hit1(h2d_i.a_address)) sel_d = SEL1;
  end

  logic a_ready_sel;
  assign a_ready_sel = (sel_d == SEL0) ? d2h_dev0_i.a_ready : d2h_dev1_i.a_ready;

  wire a_fire = h2d_i.a_valid && a_ready_sel && !outstanding_q;

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      sel_q <= SEL0;
      outstanding_q <= 1'b0;
    end else begin
      if (a_fire) begin
        sel_q <= sel_d;
        outstanding_q <= 1'b1;
      end
      if (outstanding_q) begin
        if ((sel_q==SEL0 && d2h_dev0_i.d_valid && h2d_i.d_ready) ||
            (sel_q==SEL1 && d2h_dev1_i.d_valid && h2d_i.d_ready)) begin
          outstanding_q <= 1'b0;
        end
      end
    end
  end

  always_comb begin
    h2d_dev0_o = '0;
    h2d_dev1_o = '0;
    d2h_o      = '0;

    if (!outstanding_q) begin
      if (sel_d == SEL0) begin
        h2d_dev0_o = h2d_i;
        d2h_o.a_ready = d2h_dev0_i.a_ready;
      end else begin
        h2d_dev1_o = h2d_i;
        d2h_o.a_ready = d2h_dev1_i.a_ready;
      end
    end else begin
      d2h_o.a_ready = 1'b0;
    end

    if (outstanding_q) begin
      if (sel_q == SEL0) begin
        d2h_o = d2h_dev0_i;
        h2d_dev0_o.d_ready = h2d_i.d_ready;
      end else begin
        d2h_o = d2h_dev1_i;
        h2d_dev1_o.d_ready = h2d_i.d_ready;
      end
    end
  end
endmodule
