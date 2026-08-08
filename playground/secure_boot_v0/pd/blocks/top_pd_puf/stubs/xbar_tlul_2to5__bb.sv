// Auto-generated black-box stub (ports from netlist), hand-extended from
// xbar_tlul_2to4__bb.sv with the 5th (PUF) device port -- same tl_d_*_i/o
// pattern as tl_d_uart_i/o, widths match tl_h2d_t=114b/tl_d2h_t=66b.
(* blackbox *)
module xbar_tlul_2to5 (clk_i,
    rst_ni,
    scanmode_i,
    tl_d_dmem_i,
    tl_d_dmem_o,
    tl_d_esram_i,
    tl_d_esram_o,
    tl_d_rom_i,
    tl_d_rom_o,
    tl_d_uart_i,
    tl_d_uart_o,
    tl_d_puf_i,
    tl_d_puf_o,
    tl_h_d_i,
    tl_h_d_o,
    tl_h_i_i,
    tl_h_i_o);
   input clk_i;
   input rst_ni;
   input [3:0] scanmode_i;
   input [65:0] tl_d_dmem_i;
   output [113:0] tl_d_dmem_o;
   input [65:0] tl_d_esram_i;
   output [113:0] tl_d_esram_o;
   input [65:0] tl_d_rom_i;
   output [113:0] tl_d_rom_o;
   input [65:0] tl_d_uart_i;
   output [113:0] tl_d_uart_o;
   input [65:0] tl_d_puf_i;
   output [113:0] tl_d_puf_o;
   input [113:0] tl_h_d_i;
   output [65:0] tl_h_d_o;
   input [113:0] tl_h_i_i;
   output [65:0] tl_h_i_o;
endmodule
