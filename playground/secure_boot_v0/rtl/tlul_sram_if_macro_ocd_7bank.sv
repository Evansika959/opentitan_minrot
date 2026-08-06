// Multi-bank scale-up test of the OCD macro swap. Extends the validated
// single-bank tlul_sram_if_macro_ocd_test to NumBanks x 256-word (1 KiB)
// tiles, to sanity-check bank addressing/cross-talk before committing to
// a full 21-bank (21 KiB) P&R run.
module tlul_sram_if_macro_ocd_7bank #(
  parameter int unsigned SramAw    = 16,        // address width seen on the bus
  parameter logic [31:0] BASE_ADDR = 32'h0,     // window base (byte address)
  parameter bit          READ_ONLY = 1'b0,
  parameter int unsigned NumBanks  = 7           // number of 1 KiB (256-word) tiles
) (
  input  logic                  clk_i,
  input  logic                  rst_ni,
  input  tlul_pkg::tl_h2d_t     tl_i,
  output tlul_pkg::tl_d2h_t     tl_o,
  input  prim_mubi_pkg::mubi4_t en_ifetch_i
);
  import tlul_pkg::*;

  localparam int unsigned MacroAw    = 8;                         // 256 words per bank
  localparam int unsigned BankSelW   = (NumBanks > 1) ? $clog2(NumBanks) : 1;

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

  // Window-relative word index (BASE_ADDR subtracted the same way the
  // original single-bank file did -- addr is treated as already
  // word-aligned/masked to SramAw here, consistent with the validated
  // single-bank test).
  logic [SramAw-1:0] local_addr;
  assign local_addr = addr - BASE_ADDR[2 +: SramAw];

  // Which of the NumBanks 256-word tiles this access targets, and the
  // word address within that tile.
  logic [BankSelW-1:0] bank_idx;
  logic [MacroAw-1:0]  macro_addr;
  assign bank_idx   = local_addr[MacroAw +: BankSelW];
  assign macro_addr = local_addr[MacroAw-1:0];

  // Writes are gated off for a ROM.
  logic write_eff;
  assign write_eff = we & ~READ_ONLY;

  // One-hot per-bank request qualifier.
  logic [NumBanks-1:0] bank_sel;
  for (genvar i = 0; i < NumBanks; i++) begin : gen_bank_sel
    assign bank_sel[i] = req & (bank_idx == i[BankSelW-1:0]);
  end

  logic [31:0] rdata_banks [NumBanks];

  for (genvar i = 0; i < NumBanks; i++) begin : gen_macros
    prim_ram_1p_macro_OCD #(
      .Width(32), .Depth(256), .DataBitsPerMask(8)
    ) u_mem (
      .clk_i, .rst_ni,
      .req_i     (bank_sel[i]),
      .write_i   (write_eff),
      .addr_i    (macro_addr),
      .wdata_i   (wdata),
      .wmask_i   (wmask),
      .rdata_o   (rdata_banks[i]),
      .cfg_i     ('0),
      .cfg_rsp_o ()
    );
  end

  // Register bank_idx by 1 cycle to align with the macro's registered
  // read output, same 1-cycle latency as the original single-bank file.
  logic [BankSelW-1:0] bank_idx_q;
  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      rvalid     <= 1'b0;
      bank_idx_q <= '0;
    end else begin
      rvalid     <= req & ~we;
      bank_idx_q <= bank_idx;
    end
  end

  assign rdata = rdata_banks[bank_idx_q];

  logic unused;
  assign unused = ^{req_type, addr[SramAw-1:MacroAw+BankSelW]};

endmodule : tlul_sram_if_macro_ocd_7bank
