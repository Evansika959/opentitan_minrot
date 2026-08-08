// PD-aligned TL-UL 1 KiB SRAM/ROM block for the LibreLane + LVS flow.
//
// Keeps the vendor tlul_adapter_sram exactly as the behavioural tlul_sram_if /
// tlul_rom_if do, but replaces the inline reg-array with prim_ram_1p_macro
// (4x gf180 sram256x8). One module serves all three memories on the floorplan:
//   ROM  : READ_ONLY=1   (writes ignored)
//   IMEM : READ_ONLY=0
//   DMEM : READ_ONLY=0
//
// Read latency is 1 cycle (the macro's native synchronous read); note the
// behavioural models read in 2 cycles, so reconcile that before netlist co-sim.
module tlul_sram_if_macro_ocd_test #(
  parameter int unsigned SramAw    = 16,        // address width seen on the bus
  parameter logic [31:0] BASE_ADDR = 32'h0,     // window base (byte address)
  parameter bit          READ_ONLY = 1'b0
) (
  input  logic                  clk_i,
  input  logic                  rst_ni,
  input  tlul_pkg::tl_h2d_t     tl_i,
  output tlul_pkg::tl_d2h_t     tl_o,
  input  prim_mubi_pkg::mubi4_t en_ifetch_i
);
  import tlul_pkg::*;

  localparam int unsigned MacroAw = 8;          // 256 words = 1 KiB @ 32-bit

  logic                  req, we, gnt, rvalid;
  prim_mubi_pkg::mubi4_t req_type;
  logic [SramAw-1:0]     addr;
  logic [31:0]           wdata, wmask, rdata;   // SramDw=32, no integrity bits
  logic [1:0]            rerror;

  assign gnt    = 1'b1;
  assign rerror = 2'b00;

  tlul_adapter_sram #(
    .SramAw(SramAw), .SramDw(32), .Outstanding(1), .ByteAccess(1),
    .CmdIntgCheck(0), .EnableRspIntgGen(0), .EnableDataIntgGen(0), .EnableDataIntgPt(0)
  ) u_adapt (
    .clk_i, .rst_ni, .tl_i, .tl_o, .en_ifetch_i,
    .req_o(req), .req_type_o(req_type), .gnt_i(gnt),
    .we_o(we), .addr_o(addr), .wdata_o(wdata), .wmask_o(wmask),
    .intg_error_o(),
    .user_rsvd_o(),
    .rdata_i(rdata), .rvalid_i(rvalid), .rerror_i(rerror),
    .compound_txn_in_progress_o(),
    .readback_en_i(prim_mubi_pkg::MuBi4False),
    .readback_error_o(),
    .wr_collision_i(1'b0),
    .write_pending_i(1'b0)
  );

  // Window-relative word index into the 256-entry array (block holds 256 words).
  logic [MacroAw-1:0] macro_addr;
  assign macro_addr = addr[MacroAw-1:0] - BASE_ADDR[2 +: MacroAw];

  // Writes are gated off for a ROM.
  logic write_eff;
  assign write_eff = we & ~READ_ONLY;

  // The adapter's wmask_o is already the full 32-bit bit-level write mask.
  prim_ram_1p_macro_OCD #(
    .Width(32), .Depth(256), .DataBitsPerMask(8)
  ) u_mem (
    .clk_i, .rst_ni,
    .req_i     (req),
    .write_i   (write_eff),
    .addr_i    (macro_addr),
    .wdata_i   (wdata),
    .wmask_i   (wmask),
    .rdata_o   (rdata),
    .cfg_i     ('0),
    .cfg_rsp_o ()
  );

  // 1-cycle synchronous read: rvalid for granted reads only, aligned with Q.
  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) rvalid <= 1'b0;
    else         rvalid <= req & ~we;
  end

  logic unused;
  assign unused = ^{req_type, addr[SramAw-1:MacroAw]};

endmodule
