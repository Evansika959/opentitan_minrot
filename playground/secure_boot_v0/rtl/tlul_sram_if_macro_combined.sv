// tlul_sram_if_macro_combined.sv -- new file.
//
// Combines IMEM, ESRAM, and DMEM into ONE hardened macro instead of three
// separate ones, for the naive-3-stage secure boot area experiment. Each
// region is a separate instance of the proven tlul_sram_if_macro_ocd_multibank_gen
// module (identical logic to the already-hardened 21-bank/7-bank blocks,
// just parameterized per region), with its own independent TL-UL port --
// this is purely a physical-integration convenience (one shared die/PDN
// instead of three, avoiding 2x duplicated PDN ring/margin overhead), NOT
// a change to any bus/addressing logic upstream.
//
// Bank counts sized from REAL measured software (rv32imc + -Os, gc-sections):
//   IMEM   (u_imem)  = 7 banks (7 KiB)  -- rom.c: 6268 B measured
//   ESRAM  (u_esram) = 9 banks (9 KiB)  -- rom_ext.c (6334 B) resident +
//                       bl0.c (102 B) copied-to + ~1.5KiB stack headroom,
//                       rounded up from the 8-bank raw minimum for margin
//   DMEM   (u_dmem)  = 8 banks (8 KiB)  -- packed rom_ext container (6334+128B)
//                       + bl0 container (102+128B), rounded up from the
//                       7-bank raw minimum for margin
// Total 24 banks, chosen (not just summed) to tile cleanly as a 3-column x
// 8-row grid using the SAME per-bank/per-lane geometry already proven in
// the original 21-bank layout (X=50/400/750/1100 per column, 280um row
// pitch) -- reusing that exact channel width was the fix for the DRC
// via-array issue found when a taller/narrower 1-column layout left wide
// uninterrupted PDN stripe channels between rows.
module tlul_sram_if_macro_combined (
  input  logic                  clk_i,
  input  logic                  rst_ni,

  input  tlul_pkg::tl_h2d_t     tl_imem_i,
  output tlul_pkg::tl_d2h_t     tl_imem_o,
  input  prim_mubi_pkg::mubi4_t en_ifetch_imem_i,

  input  tlul_pkg::tl_h2d_t     tl_esram_i,
  output tlul_pkg::tl_d2h_t     tl_esram_o,
  input  prim_mubi_pkg::mubi4_t en_ifetch_esram_i,

  input  tlul_pkg::tl_h2d_t     tl_dmem_i,
  output tlul_pkg::tl_d2h_t     tl_dmem_o,
  input  prim_mubi_pkg::mubi4_t en_ifetch_dmem_i
);

  tlul_sram_if_macro_ocd_multibank_gen #(
    .NumBanks(7), .READ_ONLY(1'b1)
  ) u_imem (
    .clk_i, .rst_ni,
    .tl_i(tl_imem_i), .tl_o(tl_imem_o),
    .en_ifetch_i(en_ifetch_imem_i)
  );

  tlul_sram_if_macro_ocd_multibank_gen #(
    .NumBanks(9), .READ_ONLY(1'b0)
  ) u_esram (
    .clk_i, .rst_ni,
    .tl_i(tl_esram_i), .tl_o(tl_esram_o),
    .en_ifetch_i(en_ifetch_esram_i)
  );

  tlul_sram_if_macro_ocd_multibank_gen #(
    .NumBanks(8), .READ_ONLY(1'b0)
  ) u_dmem (
    .clk_i, .rst_ni,
    .tl_i(tl_dmem_i), .tl_o(tl_dmem_o),
    .en_ifetch_i(en_ifetch_dmem_i)
  );

endmodule
