// PD-aligned TL-UL SRAM/ROM block using tiled 256-word macros for the LibreLane + LVS flow.
//
// Keeps the vendor tlul_adapter_sram exactly as the behavioural tlul_sram_if /
// tlul_rom_if do, but replaces the inline reg-array with tiled prim_ram_1p_macro
// instances (256-word/1KB blocks) automatically scaled to cover the FULL
// SramAw-bit address space, not a fixed 4KB window.
//
// FIX vs. previous version: NumBlocks was hardcoded to 4 (covering only 4KB),
// while software addresses up to the full SramAw window (e.g. 64KB for
// SramAw=16). Addresses beyond the hardcoded 4KB were silently discarded via
// the `unused` catch-all, aliasing every 4KB-aligned address onto the same
// physical 4KB -- e.g. 0x21018 and 0x20018 read/wrote the identical macro
// cell. NumBlocks is now derived from SramAw so the full address space is
// actually backed by real, distinct storage.
//
//   ROM  : READ_ONLY=1   (writes ignored)
//   IMEM : READ_ONLY=0
//   DMEM : READ_ONLY=0
//
// Read latency is 1 cycle (the macro's native synchronous read) plus the
// existing 1-cycle rvalid alignment stage (2 cycles total from req to rvalid).
module tlul_sram_if_macro #(
  parameter int unsigned SramAw     = 16,        // address width seen on the bus (byte address)
  parameter logic [31:0] BASE_ADDR  = 32'h0,     // window base (byte address)
  parameter bit          READ_ONLY  = 1'b0
) (
  input  logic                      clk_i,
  input  logic                      rst_ni,
  input  tlul_pkg::tl_h2d_t         tl_i,
  output tlul_pkg::tl_d2h_t         tl_o,
  input  prim_mubi_pkg::mubi4_t     en_ifetch_i
);
  import tlul_pkg::*;

  // Each macro block is a fixed 256-word (1 KiB @ 32-bit) tile.
  localparam int unsigned BlockAw   = 8;                     // 256 words = 8 word-address bits
  localparam int unsigned WordAw    = SramAw - 2;             // word-address bits from the full byte address
  localparam int unsigned NumBlocks = 1 << (WordAw - BlockAw); // auto-scaled to cover the FULL SramAw window
  localparam int unsigned BlockSelW = (NumBlocks > 1) ? $clog2(NumBlocks) : 1;

  logic                     req, we, gnt, rvalid;
  prim_mubi_pkg::mubi4_t    req_type;
  logic [SramAw-1:0]        addr;
  logic [31:0]              wdata, wmask, rdata;   // SramDw=32, no integrity bits
  logic [1:0]               rerror;

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

  // Full word-address index into the entire NumBlocks*256-word array.
  logic [WordAw-1:0] word_addr;
  assign word_addr = addr[SramAw-1:2];

  // Which of the NumBlocks 256-word tiles this access targets.
  logic [BlockSelW-1:0] block_idx;
  assign block_idx = word_addr[WordAw-1:BlockAw];

  // Address within the selected 256-word tile.
  logic [BlockAw-1:0] intra_block_addr;
  assign intra_block_addr = word_addr[BlockAw-1:0];

  // Writes are gated off for a ROM.
  logic write_eff;
  assign write_eff = we & ~READ_ONLY;

  // One-hot select across all tiles.
  logic [NumBlocks-1:0] block_sel;
  for (genvar i = 0; i < NumBlocks; i++) begin : gen_block_sel
    assign block_sel[i] = req & (block_idx == i[BlockSelW-1:0]);
  end

  logic [31:0] rdata_blocks [NumBlocks];

  for (genvar i = 0; i < NumBlocks; i++) begin : gen_macros
    prim_ram_1p_macro #(
      .Width(32), .Depth(256), .DataBitsPerMask(8)
    ) u_mem (
      .clk_i, .rst_ni,
      .req_i     (block_sel[i]),
      .write_i   (write_eff),
      .addr_i    (intra_block_addr),
      .wdata_i   (wdata),
      .wmask_i   (wmask),
      .rdata_o   (rdata_blocks[i]),
      .cfg_i     ('0),
      .cfg_rsp_o ()
    );
  end

  // FIX: register block_idx alongside rvalid/rvalid_q so the read-data mux
  // uses the tile that was ACTUALLY selected at request time, not whatever
  // address happens to be on the bus when the response arrives one cycle
  // later. With only one outstanding transaction this was benign in practice,
  // but is now correct by construction rather than by assumption.
  logic rvalid_q;
  logic [BlockSelW-1:0] block_idx_q1, block_idx_q2;

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      rvalid_q     <= 1'b0;
      rvalid       <= 1'b0;
      block_idx_q1 <= '0;
      block_idx_q2 <= '0;
    end else begin
      rvalid_q     <= req & ~we;
      rvalid       <= rvalid_q; // delay rvalid by 1 cycle so d_valid aligns with SRAM data output
      block_idx_q1 <= block_idx;
      block_idx_q2 <= block_idx_q1;
    end
  end

  // Mux using the block index captured at the ORIGINAL request cycle
  // (2 cycles back, matching the 2-cycle req->rvalid latency above).
  assign rdata = rdata_blocks[block_idx_q2];

  logic unused;
  assign unused = ^{req_type, addr[1:0]};

endmodule
