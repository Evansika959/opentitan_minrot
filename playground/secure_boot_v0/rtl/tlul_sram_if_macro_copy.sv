// PD-aligned TL-UL SRAM/ROM block using tiled 256-word macros for the LibreLane + LVS flow.
//
// Keeps the vendor tlul_adapter_sram exactly as the behavioural tlul_sram_if /
// tlul_rom_if do, but replaces the inline reg-array with tiled prim_ram_1p_macro
// instances (256-word/1KB blocks) automatically scaled to cover the FULL
// window, not a fixed 4KB block.
//
// FIX 3 (this version, the real bug): addr_o from tlul_adapter_sram is the
// full SYSTEM word address (already >>2'd by the adapter, NOT a raw byte
// address), truncated to SramAw bits -- it is NOT a 0-based offset into this
// window. The original tlul_sram_if.sv correctly subtracts BASE_ADDR (as a
// word address) before indexing; this file never did, and additionally
// mis-applied an extra >>2 as if addr were still byte-addressed. Both bugs
// are fixed here by mirroring the original's exact address handling.
// This explains why ESRAM (BASE_ADDR=0, subtracting 0 is a no-op) appeared
// to work while DMEM (BASE_ADDR=0x20000) never did.
//
//   ROM  : READ_ONLY=1   (writes ignored)
//   IMEM : READ_ONLY=0
//   DMEM : READ_ONLY=0
//
// Read latency is 1 cycle (the macro's native synchronous read) plus the
// existing 1-cycle rvalid alignment stage (2 cycles total from req to rvalid).
module tlul_sram_if_macro #(
  parameter int unsigned SramAw      = 16,        // address width seen on the bus (word address, per adapter)
  parameter logic [31:0] BASE_ADDR   = 32'h0,      // window base (byte address)
  parameter bit          READ_ONLY   = 1'b0,
  parameter string        INIT_HEX   = "",         // optional backdoor preload file, one 32-bit hex word/line
  parameter int unsigned WindowWords = 16384       // words actually backed by real macros (64 KiB @ 32-bit default)
) (
  input  logic                      clk_i,
  input  logic                      rst_ni,
  input  tlul_pkg::tl_h2d_t         tl_i,
  output tlul_pkg::tl_d2h_t         tl_o,
  input  prim_mubi_pkg::mubi4_t     en_ifetch_i
);
  import tlul_pkg::*;

  // Each macro block is a fixed 256-word (1 KiB @ 32-bit) tile.
  localparam int unsigned BlockAw   = 8;                          // 256 words = 8 word-address bits
  localparam int unsigned NumBlocks = WindowWords / 256;           // e.g. 64 tiles for a 64 KiB window
  localparam int unsigned WordAw    = $clog2(WindowWords);         // e.g. 14 bits for 16384 words
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

  // FIX: addr is already a word address (per tlul_adapter_sram's own
  // convention -- confirmed against the original tlul_sram_if.sv, which
  // subtracts BASE_ADDR directly with no extra >>2). Subtract BASE_ADDR
  // (as a word address) to get a 0-based index into THIS window.
  logic [SramAw-1:0] local_addr;
  assign local_addr = addr - BASE_ADDR[31:2];

  // Which of the NumBlocks 256-word tiles this access targets.
  logic [BlockSelW-1:0] block_idx;
  assign block_idx = local_addr[WordAw-1:BlockAw];

  // Address within the selected 256-word tile.
  logic [BlockAw-1:0] intra_block_addr;
  assign intra_block_addr = local_addr[BlockAw-1:0];

  // Writes are gated off for a ROM.
  logic write_eff;
  assign write_eff = we & ~READ_ONLY;

  // One-hot select across all tiles.
  logic [NumBlocks-1:0] block_sel;
  for (genvar i = 0; i < NumBlocks; i++) begin : gen_block_sel
    assign block_sel[i] = req & (block_idx == i[BlockSelW-1:0]);
  end

  logic [31:0] rdata_blocks [NumBlocks];

`ifndef SYNTHESIS
  logic [31:0] init_words [0:WindowWords-1];
  initial begin
    if (INIT_HEX != "") begin
      $readmemh(INIT_HEX, init_words);
      $display("[PRELOAD DEBUG] INIT_HEX=%s init_words[0x406]=%08h", INIT_HEX, init_words[16'h406]);
    end
  end
`endif

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

`ifndef SYNTHESIS
    initial begin
      if (INIT_HEX != "") begin
        for (int off = 0; off < 256; off++) begin
          gen_macros[i].u_mem.gen_byte[0].u_macro.mem[off] = init_words[i*256+off][7:0];
          gen_macros[i].u_mem.gen_byte[1].u_macro.mem[off] = init_words[i*256+off][15:8];
          gen_macros[i].u_mem.gen_byte[2].u_macro.mem[off] = init_words[i*256+off][23:16];
          gen_macros[i].u_mem.gen_byte[3].u_macro.mem[off] = init_words[i*256+off][31:24];
        end
        if (i == 4) $display("[PRELOAD DEBUG block4] mem[6] lanes: b0=%02h b1=%02h b2=%02h b3=%02h (expect 00 00 01 00)",
          gen_macros[i].u_mem.gen_byte[0].u_macro.mem[6],
          gen_macros[i].u_mem.gen_byte[1].u_macro.mem[6],
          gen_macros[i].u_mem.gen_byte[2].u_macro.mem[6],
          gen_macros[i].u_mem.gen_byte[3].u_macro.mem[6]);
      end
    end
`endif
  end

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
      rvalid       <= rvalid_q;
      block_idx_q1 <= block_idx;
      block_idx_q2 <= block_idx_q1;
    end
  end

  assign rdata = rdata_blocks[block_idx_q2];

  always @(posedge clk_i) begin
    if (tl_i.a_valid && (tl_i.a_address == 32'h00021018))
      $display("[ENTRY_ADDR READ] req a_address=0x%08h a_opcode=%0d", tl_i.a_address, tl_i.a_opcode);
    if (req)
      $display("[ADDR CALC] req=1 addr(adapter)=0x%08h local_addr=0x%08h block_idx=%0d intra_block_addr=0x%02h",
                addr, local_addr, block_idx, intra_block_addr);
    if (rvalid_q || rvalid)
      $display("[PIPE] rvalid_q=%0b rvalid=%0b block_idx_q1=%0d block_idx_q2=%0d rdata_blocks[4]=%08h rdata=%08h",
                rvalid_q, rvalid, block_idx_q1, block_idx_q2, rdata_blocks[4], rdata);
    if (tl_o.d_valid)
      $display("[ENTRY_ADDR RESP] d_data=0x%08h", tl_o.d_data);
  end

  logic unused;
  assign unused = ^{req_type};

endmodule
