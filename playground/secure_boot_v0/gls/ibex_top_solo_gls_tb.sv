// ibex_top_solo_gls_tb.sv -- new file.
//
// Standalone GLS testbench for the ALREADY-INDEPENDENTLY-HARDENED
// ibex_top netlist (pd/macros/ibex_top/ibex_top.nl.v) -- no TL-UL, no
// xbar, no uart, no real memory macros. Drives ibex's raw OBI-style
// instr_*/data_* ports directly with a trivial testbench-side word-
// addressable memory model.
//
// Why: the top_pd_puf integration smoke test shows the CPU fetches ~2
// instructions then goes quiet (mcycle keeps counting, so it's not held
// in reset), and a follow-up probe showed the data-side TL-UL adapter
// (u_data2tl.outstanding_q) NEVER launches a single transaction in the
// whole run -- not even the very first UART_CTRL store. This test isolates
// whether that's an ibex_top-side defect (never asserts data_req_o, or
// mishandles the very first store) or something downstream of it
// (xbar_tlul_2to5 -- the one genuinely new, never-independently-hardened
// piece in this design -- or uart, which showed the same suspicious
// mostly-unreset-flop ratio tlul_sram_if_macro did before the DFF
// simpatch fix).
//
// Program (gls/ibex_solo_boot.S, assembled to gls/ibex_solo/ibex_solo.imem.hex):
// li+store+load+compare+branch, then writes a magic value to 0x2000 (PASS)
// or 0x3000 (FAIL) depending on whether the load matched the store. Same
// reset-vector-at-offset-0x80 convention as smoke_puf_boot.S (Ibex always
// fetches its first instruction from {boot_addr_i[31:8], 8'h80}).
//
// Port-less, self-contained, self-clocking/self-resetting -- same
// convention as tlul_sram_if_macro_solo_gls_tb.sv / top_pd_puf_smoke_gls_tb.sv
// (verilator --binary, no custom C++ main).
`timescale 1ns/1ps

module ibex_top_solo_gls_tb;

  logic clk;
  logic rst_n;
  initial clk = 0;
  always #30 clk = ~clk;

  initial begin
    rst_n = 0;
    repeat (8) @(posedge clk);
    rst_n = 1;
  end

  // ---------------------------------------------------------------------
  // DUT: the already-independently-hardened ibex_top netlist, nothing else.
  // Tie-offs copied exactly from rtl/top_pd_puf.sv's own u_ibex instance.
  // ---------------------------------------------------------------------
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

  // ---------------------------------------------------------------------
  // Instruction memory BFM: single-outstanding, 1-cycle latency, always
  // grants. Preloaded from the assembled program.
  // ---------------------------------------------------------------------
  logic [31:0] imem [0:255];
  initial begin
    string imem_hex;
    if (!$value$plusargs("gls_ibex_imem_hex=%s", imem_hex)) begin
      $display("[IBEX_SOLO_GLS] FAIL: missing +gls_ibex_imem_hex= plusarg");
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
  // Data memory BFM: single-outstanding, 1-cycle latency, always grants.
  // Only three addresses matter for this program: 0x1000 (scratch,
  // real storage), 0x2000 (PASS marker), 0x3000 (FAIL marker). Anything
  // else is acked harmlessly with rdata=0 so unexpected traffic (if any)
  // doesn't itself deadlock the core.
  // ---------------------------------------------------------------------
  logic [31:0] scratch_1000;
  logic data_busy;
  logic data_busy_we;
  logic [31:0] data_addr_q, data_wdata_q;
  assign data_gnt = data_req && !data_busy;

  bit pass_seen, fail_seen;
  logic [31:0] pass_fail_data;

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      data_busy     <= 1'b0;
      data_rvalid   <= 1'b0;
      data_rdata    <= 32'h0;
      scratch_1000  <= 32'h0;
      pass_seen     <= 1'b0;
      fail_seen     <= 1'b0;
    end else begin
      data_rvalid <= 1'b0;
      if (data_gnt) begin
        data_busy    <= 1'b1;
        data_busy_we <= data_we;
        data_addr_q  <= data_addr;
        data_wdata_q <= data_wdata;
        // Writes take effect the same cycle they're granted (matches a
        // simple always-ready memory model); reads are returned next cycle.
        if (data_we) begin
          case (data_addr)
            32'h0000_1000: scratch_1000 <= data_wdata;
            32'h0000_2000: begin pass_seen <= 1'b1; pass_fail_data <= data_wdata; end
            32'h0000_3000: begin fail_seen <= 1'b1; pass_fail_data <= data_wdata; end
            default: ;
          endcase
        end
      end
      if (data_busy) begin
        data_busy   <= 1'b0;
        data_rvalid <= 1'b1;
        if (!data_busy_we) begin
          case (data_addr_q)
            32'h0000_1000: data_rdata <= scratch_1000;
            default:       data_rdata <= 32'h0;
          endcase
        end else begin
          data_rdata <= 32'h0;
        end
      end
    end
  end

  // ---------------------------------------------------------------------
  // Diagnostics + pass/fail.
  // ---------------------------------------------------------------------
  int instr_fetch_count, data_txn_count;
  initial begin
    instr_fetch_count = 0;
    data_txn_count = 0;
  end
  always_ff @(posedge clk) begin
    if (instr_gnt) begin
      instr_fetch_count <= instr_fetch_count + 1;
      if (instr_fetch_count < 20)
        $display("[IBEX_SOLO_GLS][INSTR] t=%0t addr=0x%08h", $time, instr_addr);
    end
    if (data_gnt) begin
      data_txn_count <= data_txn_count + 1;
      $display("[IBEX_SOLO_GLS][DATA] t=%0t addr=0x%08h we=%b wdata=0x%08h", $time, data_addr, data_we, data_wdata);
    end
  end

  initial begin
    @(posedge rst_n);
    wait (pass_seen || fail_seen);
    @(posedge clk); #1;
    $display("");
    $display("[IBEX_SOLO_GLS] instr fetches=%0d, data transactions=%0d", instr_fetch_count, data_txn_count);
    if (pass_seen)
      $display("[IBEX_SOLO_GLS] PASS: gate-level ibex_top fetched, stored, loaded, and compared correctly (wrote 0x%08h to PASS marker).", pass_fail_data);
    else
      $display("[IBEX_SOLO_GLS] FAIL: load-after-store mismatch inside the CPU itself (wrote 0x%08h to FAIL marker, i.e. the mismatching loaded value).", pass_fail_data);
    $finish;
  end

  initial begin
    #500000;
    $display("");
    $display("[IBEX_SOLO_GLS] instr fetches=%0d, data transactions=%0d", instr_fetch_count, data_txn_count);
    $display("[IBEX_SOLO_GLS] FAIL: timed out -- neither PASS (0x2000) nor FAIL (0x3000) marker was ever written.");
    $finish;
  end

endmodule
