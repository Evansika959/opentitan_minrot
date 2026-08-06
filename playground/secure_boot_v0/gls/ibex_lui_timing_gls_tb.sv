// ibex_lui_timing_gls_tb.sv -- new file.
//
// Sibling of ibex_top_solo_gls_tb.sv, same DUT instantiation/tie-offs
// (verified correct against ibex_top's own RTL there), but a fully
// generic data memory BFM (any address, no special-casing) and no
// PASS/FAIL gating -- this is a diagnostic dump, not a directed test.
// Runs gls/ibex_lui_timing_boot.S (five `lui t0,0xcafef` + store, each
// with 0..4 NOPs of delay before the store) and prints every data write
// it sees, then a summary table, to find out whether ANY delay makes the
// stored value correct (0xcafef000) -- timing/hazard bug -- or it's wrong
// at every delay -- LUI computation itself is wrong.
`timescale 1ns/1ps

module ibex_lui_timing_gls_tb;

  logic clk;
  logic rst_n;
  initial clk = 0;
  always #30 clk = ~clk;

  initial begin
    rst_n = 0;
    repeat (8) @(posedge clk);
    rst_n = 1;
  end

  logic        instr_req, instr_gnt, instr_rvalid, instr_err;
  logic [31:0] instr_addr, instr_rdata;
  logic        data_req, data_gnt, data_rvalid, data_we, data_err;
  logic [3:0]  data_be;
  logic [31:0] data_addr, data_wdata, data_rdata;

  localparam logic [3:0] IBEX_MUBI_ON = 4'b0101; // ibex_pkg::IbexMuBiOn

  ibex_top dut (
    .clk_i(clk), .rst_ni(rst_n), .test_en_i(1'b0),
    .ram_cfg_icache_tag_i(12'h0), .ram_cfg_rsp_icache_tag_o(),
    .ram_cfg_icache_data_i(12'h0), .ram_cfg_rsp_icache_data_o(),
    .hart_id_i(32'h0), .boot_addr_i(32'h0),
    .instr_req_o(instr_req), .instr_gnt_i(instr_gnt), .instr_rvalid_i(instr_rvalid),
    .instr_addr_o(instr_addr), .instr_rdata_i(instr_rdata), .instr_rdata_intg_i(7'h0), .instr_err_i(instr_err),
    .data_req_o(data_req), .data_gnt_i(data_gnt), .data_rvalid_i(data_rvalid),
    .data_we_o(data_we), .data_be_o(data_be), .data_addr_o(data_addr), .data_wdata_o(data_wdata),
    .data_wdata_intg_o(), .data_rdata_i(data_rdata), .data_rdata_intg_i(7'h0), .data_err_i(data_err),
    .irq_software_i(1'b0), .irq_timer_i(1'b0), .irq_external_i(1'b0), .irq_fast_i(15'h0), .irq_nm_i(1'b0),
    .fetch_enable_i(IBEX_MUBI_ON),
    .alert_minor_o(), .alert_major_internal_o(),
    .alert_major_bus_o(), .core_sleep_o(), .scan_rst_ni(1'b1),
    .scramble_key_valid_i(1'b0), .scramble_key_i(128'h0), .scramble_nonce_i(64'h0), .scramble_req_o(),
    .debug_req_i(1'b0), .crash_dump_o(), .double_fault_seen_o()
  );

  assign instr_err = 1'b0;
  assign data_err  = 1'b0;

  logic [31:0] imem [0:255];
  initial begin
    string imem_hex;
    if (!$value$plusargs("gls_ibex_imem_hex=%s", imem_hex)) begin
      $display("[IBEX_LUI_TIMING_GLS] FAIL: missing +gls_ibex_imem_hex= plusarg");
      $finish;
    end
    $readmemh(imem_hex, imem);
  end

  logic instr_busy;
  logic [31:0] instr_addr_q;
  assign instr_gnt = instr_req && !instr_busy;

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      instr_busy   <= 1'b0;
      instr_rvalid <= 1'b0;
      instr_rdata  <= 32'h0;
    end else begin
      instr_rvalid <= 1'b0;
      if (instr_gnt) begin
        instr_busy   <= 1'b1;
        instr_addr_q <= instr_addr;
      end
      if (instr_busy) begin
        instr_busy   <= 1'b0;
        instr_rvalid <= 1'b1;
        instr_rdata  <= imem[instr_addr_q[9:2]];
      end
    end
  end

  // ---------------------------------------------------------------------
  // TEMP DIAGNOSTIC: prefetch buffer live-vs-buffered mux control bits.
  // Traced instr_rdata_i[16]'s fanout: it feeds 3 muxes, each choosing
  // between the live bus bit and a buffered bit from
  // gen_prefetch_buffer.prefetch_buffer_i.fifo_i.rdata_q[16/48/80], with
  // fifo_i.valid_q[0] (a dffrnq_1 -- same cell family already fixed by the
  // simpatch) directly driving the first mux's select line. Watching these
  // control bits directly to see whether the buffer's live/buffered
  // selection logic behaves sanely at runtime, or is itself the source of
  // the corruption.
  int pf_change_count;
  logic pf_valid_prev;
  initial begin
    pf_change_count = 0;
    #1;
    pf_valid_prev = dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.valid_q[0] ;
    $display("[PF_DIAG] t=%0t initial valid_q[0]=%b rdata_q[16]=%b rdata_q[48]=%b rdata_q[80]=%b",
              $time, pf_valid_prev,
              dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.rdata_q[16] ,
              dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.rdata_q[48] ,
              dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.rdata_q[80] );
    forever begin
      @(posedge clk);
      #1;
      begin
        logic pf_valid_now;
        pf_valid_now = dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.valid_q[0] ;
        if (pf_valid_now !== pf_valid_prev) begin
          pf_change_count++;
          if (pf_change_count <= 30)
            $display("[PF_DIAG] t=%0t valid_q[0] changed (#%0d): %b -> %b  rdata_q[16]=%b rdata_q[48]=%b rdata_q[80]=%b",
                      $time, pf_change_count, pf_valid_prev, pf_valid_now,
                      dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.rdata_q[16] ,
                      dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.rdata_q[48] ,
                      dut.\u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_i.rdata_q[80] );
          pf_valid_prev = pf_valid_now;
        end
      end
    end
  end

  // ---------------------------------------------------------------------
  // Generic data memory BFM: any address, 4096-word array (16 KiB,
  // comfortably covers 0x0 and 0x2000-0x2014 used here), single-outstanding,
  // 1-cycle latency, always grants.
  // ---------------------------------------------------------------------
  logic [31:0] dmem [0:4095];
  initial begin
    int i;
    for (i = 0; i < 4096; i++) dmem[i] = 32'h0;
  end

  logic data_busy, data_busy_we;
  logic [31:0] data_addr_q;
  assign data_gnt = data_req && !data_busy;

  int write_count;
  initial write_count = 0;

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      data_busy   <= 1'b0;
      data_rvalid <= 1'b0;
      data_rdata  <= 32'h0;
    end else begin
      data_rvalid <= 1'b0;
      if (data_gnt) begin
        data_busy    <= 1'b1;
        data_busy_we <= data_we;
        data_addr_q  <= data_addr;
        if (data_we) begin
          dmem[data_addr[13:2]] <= data_wdata;
          write_count <= write_count + 1;
          $display("[IBEX_LUI_TIMING_GLS][WRITE #%0d] t=%0t addr=0x%08h data=0x%08h", write_count, $time, data_addr, data_wdata);
        end
      end
      if (data_busy) begin
        data_busy   <= 1'b0;
        data_rvalid <= 1'b1;
        data_rdata  <= data_busy_we ? 32'h0 : dmem[data_addr_q[13:2]];
      end
    end
  end

  // ---------------------------------------------------------------------
  // Run until the done marker (0x2014 = 1) or timeout, then dump the
  // relevant addresses directly from the BFM's own array.
  // ---------------------------------------------------------------------
  initial begin
    @(posedge rst_n);
    wait (dmem[32'h2014>>2] == 32'h1);
    @(posedge clk); #1;
    $display("");
    $display("[IBEX_LUI_TIMING_GLS] ===== summary (expect 0xcafef000 at every delay if this is a timing issue) =====");
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00000000 (s0 sanity, expect 0x00002000) = 0x%08h", dmem[32'h0000>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002000 (delay=0)                      = 0x%08h", dmem[32'h2000>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002004 (delay=1)                      = 0x%08h", dmem[32'h2004>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002008 (delay=2)                      = 0x%08h", dmem[32'h2008>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x0000200c (delay=3)                      = 0x%08h", dmem[32'h200c>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002010 (delay=4)                      = 0x%08h", dmem[32'h2010>>2]);
    $finish;
  end

  initial begin
    #500000;
    $display("[IBEX_LUI_TIMING_GLS] FAIL: timed out -- done marker (0x2014) never written.");
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00000000 = 0x%08h", dmem[32'h0000>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002000 = 0x%08h", dmem[32'h2000>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002004 = 0x%08h", dmem[32'h2004>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002008 = 0x%08h", dmem[32'h2008>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x0000200c = 0x%08h", dmem[32'h200c>>2]);
    $display("[IBEX_LUI_TIMING_GLS] addr 0x00002010 = 0x%08h", dmem[32'h2010>>2]);
    $finish;
  end

endmodule
