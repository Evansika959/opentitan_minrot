// Auto-generated black-box stub (ports from netlist). Same external port
// list as tlul_sram_if_macro__bb.sv -- NumBanks/READ_ONLY/SramAw/BASE_ADDR
// only affect internal bank tiling, not the module's TL-UL boundary -- so
// this stub is structurally identical, just a different module (and
// physical-view) name: the real, already-hardened 21-bank/84-real-macro
// block (pd/blocks/tlul_sram_if_macro_ocd_21bank), exported into
// pd/macros/ via export_macros.sh.
(* blackbox *)
module tlul_sram_if_macro_ocd_21bank (clk_i,
    rst_ni,
    en_ifetch_i,
    tl_i,
    tl_o);
   input clk_i;
   input rst_ni;
   input [3:0] en_ifetch_i;
   input [113:0] tl_i;
   output [65:0] tl_o;
endmodule
