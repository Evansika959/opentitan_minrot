// top_pd_min_secboot_gls_tb.sv -- new file, forked from the proven-good
// top_pd_7bank_secboot_gls_tb.sv (that file is left untouched as the known-
// good regression reference; do not merge changes back into it).
//
// GLS testbench for the real-crypto secure-boot + PUF demo on top_pd_min
// (right-sized memories: IMEM=tlul_sram_if_macro_ocd_10bank/10KiB,
// ESRAM/DMEM=tlul_sram_if_macro_ocd_2bank/2KiB each, vs top_pd_7bank's
// uniform 7KiB everywhere). Two differences from the 7bank secboot tb this
// was forked from:
//   1. IMEM backdoor-load now unrolls all 10 banks x 4 lanes (40 $readmemh
//      calls), not 7 -- matches tlul_sram_if_macro_ocd_10bank's real
//      capacity.
//   2. DMEM backdoor-load unrolls 2 banks x 4 lanes (8 $readmemh calls),
//      not 1 -- matches tlul_sram_if_macro_ocd_2bank's real capacity
//      (still plenty for the packed signed container, which is under
//      300 bytes).
//
// Everything else (DIAG blocks, UART bit-bang decoder, PUF preload, timeout
// logic) is identical to the 7bank tb: the top-level port list and every
// hierarchical path referenced here (u_ibex, u_data2tl, u_imem, u_esram,
// u_dmem, u_puf_regif.u_puf.u_sram) are top-level instance names in
// top_pd_min.sv, unaffected by the internal bank-count change inside the
// memory macros -- confirmed against top_pd_min.sv (only the three memory
// instantiations changed types; all ibex/uart/xbar/PUF-glue wiring is
// identical to top_pd_7bank.sv).
`timescale 1ns/1ps

module top_pd_min_secboot_gls_tb;
  logic clk;
  logic rst_n;
  logic uart_rx;
  logic uart_tx, uart_tx_en;

  initial clk = 0;
  always #30 clk = ~clk;

  assign uart_rx = 1'b1; // no external UART input needed for this test

  top_pd_min dut (
    .clk_i        (clk),
    .rst_ni       (rst_n),
    .uart_rx_i    (uart_rx),
    .uart_tx_o    (uart_tx),
    .uart_tx_en_o (uart_tx_en)
  );

  // ---------------------------------------------------------------------
  // Waveform dump.
  // ---------------------------------------------------------------------
  initial begin
    $dumpfile("top_pd_min_secboot_gls.fst");
    $dumpvars(0, top_pd_min_secboot_gls_tb);
  end

  // DIAG: plain $display on uart_tx/uart_tx_en/rst_n, confirms clk is
  // running and rst_n really deasserts.
  initial begin
    $display("[DIAG] t=%0t rst_n=%b uart_tx=%b uart_tx_en=%b", $time, rst_n, uart_tx, uart_tx_en);
    forever begin
      @(uart_tx or uart_tx_en or rst_n);
      $display("[DIAG] t=%0t rst_n=%b uart_tx=%b uart_tx_en=%b", $time, rst_n, uart_tx, uart_tx_en);
    end
  end

  // DIAG_DMEM: bus activity on the DMEM macro -- added specifically because
  // the stack now lives in DMEM (link_min_rom_dmem_stack.ld): every local
  // variable push/pop the crypto call chain does is a real bus transaction
  // here, so this doubles as a live view of stack depth/activity during
  // the compute-heavy stage. Also the direct check for "does DMEM start
  // showing unexpected content/activity partway through" -- if the stack
  // (or anything else) starts writing somewhere it shouldn't, this is
  // where it would first show up.
  logic [113:0] dmem_tl_i_prev;
  logic [65:0]  dmem_tl_o_prev;
  int dmem_tl_i_changes, dmem_tl_o_changes;
  initial begin
    dmem_tl_i_changes = 0;
    dmem_tl_o_changes = 0;
    dmem_tl_i_prev = dut.u_dmem.tl_i;
    dmem_tl_o_prev = dut.u_dmem.tl_o;
    forever begin
      @(dut.u_dmem.tl_i or dut.u_dmem.tl_o);
      if (dut.u_dmem.tl_i !== dmem_tl_i_prev) begin
        dmem_tl_i_changes++;
        dmem_tl_i_prev = dut.u_dmem.tl_i;
      end
      if (dut.u_dmem.tl_o !== dmem_tl_o_prev) begin
        dmem_tl_o_changes++;
        dmem_tl_o_prev = dut.u_dmem.tl_o;
      end
    end
  end

  // HEARTBEAT: periodic progress monitor -- testbench-side only, does NOT
  // touch the ROM's compiled code, so it can't introduce the LTO-codegen
  // sensitivity that's destabilized every ROM-side debug addition so far.
  // Prints a clean (non-wrapping) cycle count, the cumulative IMEM/DMEM
  // fetch change counts since the last heartbeat, and the CURRENT raw
  // imem_tl_i/dmem_tl_i values -- lets us tell "still actively fetching,
  // just slow" (changes-per-interval stays roughly steady, tl_i value
  // varies between heartbeats) apart from "genuinely stuck/deadlocked"
  // (changes-per-interval drops to ~0, tl_i value repeats identically).
  // The dmem_tl_i address field (bits [96:65], same TL-UL layout as
  // decoded for IMEM earlier) is the actual stack address being touched --
  // watch it to see whether the stack stays in a bounded range near
  // _stack_top (0x20780) or drifts toward the container region (low
  // DMEM addresses) over the course of the run.
  longint unsigned hb_cycles;
  int hb_last_imem_tl_i_changes, hb_last_imem_tl_o_changes;
  int hb_last_dmem_tl_i_changes, hb_last_dmem_tl_o_changes;
  localparam longint unsigned HEARTBEAT_PERIOD = 200_000;
  initial begin
    hb_cycles = 0;
    hb_last_imem_tl_i_changes = 0;
    hb_last_imem_tl_o_changes = 0;
    hb_last_dmem_tl_i_changes = 0;
    hb_last_dmem_tl_o_changes = 0;
  end
  always_ff @(posedge clk) begin
    if (rst_n) begin
      hb_cycles <= hb_cycles + 1;
      if ((hb_cycles % HEARTBEAT_PERIOD) == 0 && hb_cycles != 0) begin
        $display("[HEARTBEAT] t=%0t cycles=%0d imem_i_delta=%0d imem_o_delta=%0d dmem_i_delta=%0d dmem_o_delta=%0d imem_tl_i=%h dmem_tl_i=%h",
                  $time, hb_cycles,
                  imem_tl_i_changes - hb_last_imem_tl_i_changes, imem_tl_o_changes - hb_last_imem_tl_o_changes,
                  dmem_tl_i_changes - hb_last_dmem_tl_i_changes, dmem_tl_o_changes - hb_last_dmem_tl_o_changes,
                  dut.u_imem.tl_i, dut.u_dmem.tl_i);
        hb_last_imem_tl_i_changes <= imem_tl_i_changes;
        hb_last_imem_tl_o_changes <= imem_tl_o_changes;
        hb_last_dmem_tl_i_changes <= dmem_tl_i_changes;
        hb_last_dmem_tl_o_changes <= dmem_tl_o_changes;
      end
    end
  end

  // WINDOWTRACE: fine-grained, every-REQUEST log within a narrow cycle
  // window. Originally logged every raw dmem_tl_i change, which included
  // cycles where a_valid=0 -- per TL-UL, the receiver must ignore all
  // fields (address/opcode/etc) when a_valid=0, so those samples were
  // just whatever stale/combinational value happened to be sitting on the
  // wire between real transactions, not real DMEM accesses. That produced
  // apparent "invalid addresses" (e.g. 0x6e0, 0xd02ced24) that were
  // confirmed (by decoding a_valid, the tl_h2d_t MSB, bit 113) to be
  // artifacts of an unqualified signal, not genuine bus corruption --
  // every real request (a_valid=1) had a legitimate in-range address.
  // Gated on tl_i[113] (a_valid) so only real requests are printed.
  localparam longint unsigned WINDOW_LO = 100_000;
  localparam longint unsigned WINDOW_HI = 450_000;
  logic [113:0] wt_dmem_prev;
  initial wt_dmem_prev = dut.u_dmem.tl_i;
  always_ff @(posedge clk) begin
    if (rst_n && hb_cycles >= WINDOW_LO && hb_cycles <= WINDOW_HI) begin
      if (dut.u_dmem.tl_i !== wt_dmem_prev) begin
        if (dut.u_dmem.tl_i[113]) begin
          $display("[WINDOWTRACE] cycles=%0d t=%0t dmem_tl_i=%h imem_tl_i=%h",
                    hb_cycles, $time, dut.u_dmem.tl_i, dut.u_imem.tl_i);
        end
        wt_dmem_prev <= dut.u_dmem.tl_i;
      end
    end
  end

  // DIAG2: is the CPU issuing ANY bus transaction to IMEM at all?
  logic [113:0] imem_tl_i_prev;
  logic [65:0]  imem_tl_o_prev;
  int imem_tl_i_changes, imem_tl_o_changes;
  initial begin
    imem_tl_i_changes = 0;
    imem_tl_o_changes = 0;
    imem_tl_i_prev = dut.u_imem.tl_i;
    imem_tl_o_prev = dut.u_imem.tl_o;
    forever begin
      @(dut.u_imem.tl_i or dut.u_imem.tl_o);
      if (dut.u_imem.tl_i !== imem_tl_i_prev) begin
        imem_tl_i_changes++;
        if (imem_tl_i_changes <= 10)
          $display("[DIAG2] t=%0t u_imem.tl_i changed (#%0d): %h", $time, imem_tl_i_changes, dut.u_imem.tl_i);
        imem_tl_i_prev = dut.u_imem.tl_i;
      end
      if (dut.u_imem.tl_o !== imem_tl_o_prev) begin
        imem_tl_o_changes++;
        if (imem_tl_o_changes <= 10)
          $display("[DIAG2] t=%0t u_imem.tl_o changed (#%0d): %h", $time, imem_tl_o_changes, dut.u_imem.tl_o);
        imem_tl_o_prev = dut.u_imem.tl_o;
      end
    end
  end

  // DIAG3: ibex_top's own internal clock-gate cell.
  int core_clk_toggle_count, clock_en_val, en_latch_val;
  initial begin
    core_clk_toggle_count = 0;
    clock_en_val = dut.\u_ibex.clock_en ;
    en_latch_val = dut.\u_ibex.core_clock_gate_i.en_latch ;
    $display("[DIAG3] t=%0t u_ibex.clk=%b u_ibex.clock_en=%b core_clock_gate_i.en_latch=%b",
              $time, dut.\u_ibex.clk , clock_en_val, en_latch_val);
    forever begin
      @(dut.\u_ibex.clk );
      core_clk_toggle_count++;
      if (core_clk_toggle_count <= 10)
        $display("[DIAG3] t=%0t u_ibex.clk toggled (#%0d) -> %b, clock_en=%b, en_latch=%b",
                  $time, core_clk_toggle_count, dut.\u_ibex.clk , dut.\u_ibex.clock_en , dut.\u_ibex.core_clock_gate_i.en_latch );
    end
  end

  // DIAG4: ibex_core's own free-running mcycle counter.
  wire [19:0] mcycle_lo;
  assign mcycle_lo[0]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[0] ;
  assign mcycle_lo[1]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[1] ;
  assign mcycle_lo[2]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[2] ;
  assign mcycle_lo[3]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[3] ;
  assign mcycle_lo[4]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[4] ;
  assign mcycle_lo[5]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[5] ;
  assign mcycle_lo[6]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[6] ;
  assign mcycle_lo[7]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[7] ;
  assign mcycle_lo[8]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[8] ;
  assign mcycle_lo[9]  = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[9] ;
  assign mcycle_lo[10] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[10] ;
  assign mcycle_lo[11] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[11] ;
  assign mcycle_lo[12] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[12] ;
  assign mcycle_lo[13] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[13] ;
  assign mcycle_lo[14] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[14] ;
  assign mcycle_lo[15] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[15] ;
  assign mcycle_lo[16] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[16] ;
  assign mcycle_lo[17] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[17] ;
  assign mcycle_lo[18] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[18] ;
  assign mcycle_lo[19] = dut.\u_ibex.u_ibex_core.cs_registers_i.mcycle_counter_i.counter[19] ;
  logic [19:0] mcycle_lo_prev;
  int mcycle_change_count;
  initial begin
    mcycle_change_count = 0;
    #1;
    mcycle_lo_prev = mcycle_lo;
    $display("[DIAG4] t=%0t mcycle_lo(initial)=%0d", $time, mcycle_lo);
    forever begin
      @(mcycle_lo);
      mcycle_change_count++;
      if (mcycle_change_count <= 10)
        $display("[DIAG4] t=%0t mcycle_lo changed (#%0d) -> %0d", $time, mcycle_change_count, mcycle_lo);
      mcycle_lo_prev = mcycle_lo;
    end
  end

  // DIAG5: data-side bus liveness (u_data2tl.outstanding_q + u_esram
  // tl_i/tl_o).
  logic data_outstanding_prev;
  int data_outstanding_changes;
  logic [113:0] esram_tl_i_prev;
  logic [65:0]  esram_tl_o_prev;
  int esram_tl_i_changes, esram_tl_o_changes;
  initial begin
    data_outstanding_changes = 0;
    esram_tl_i_changes = 0;
    esram_tl_o_changes = 0;
    #1;
    data_outstanding_prev = dut.\u_data2tl.outstanding_q ;
    esram_tl_i_prev = dut.u_esram.tl_i;
    esram_tl_o_prev = dut.u_esram.tl_o;
    forever begin
      @(dut.\u_data2tl.outstanding_q  or dut.u_esram.tl_i or dut.u_esram.tl_o);
      if (dut.\u_data2tl.outstanding_q  !== data_outstanding_prev) begin
        data_outstanding_changes++;
        if (data_outstanding_changes <= 20)
          $display("[DIAG5] t=%0t u_data2tl.outstanding_q changed (#%0d) -> %b", $time, data_outstanding_changes, dut.\u_data2tl.outstanding_q );
        data_outstanding_prev = dut.\u_data2tl.outstanding_q ;
      end
      if (dut.u_esram.tl_i !== esram_tl_i_prev) begin
        esram_tl_i_changes++;
        if (esram_tl_i_changes <= 10)
          $display("[DIAG5] t=%0t u_esram.tl_i changed (#%0d): %h", $time, esram_tl_i_changes, dut.u_esram.tl_i);
        esram_tl_i_prev = dut.u_esram.tl_i;
      end
      if (dut.u_esram.tl_o !== esram_tl_o_prev) begin
        esram_tl_o_changes++;
        if (esram_tl_o_changes <= 10)
          $display("[DIAG5] t=%0t u_esram.tl_o changed (#%0d): %h", $time, esram_tl_o_changes, dut.u_esram.tl_o);
        esram_tl_o_prev = dut.u_esram.tl_o;
      end
    end
  end

  // ---------------------------------------------------------------------
  // Optional PUF entropy-source preload.
  // ---------------------------------------------------------------------
  initial begin
    string realdata_hex;
    #1;
    if ($value$plusargs("gls_realdata_hex=%s", realdata_hex)) begin
      $readmemh(realdata_hex, dut.\u_puf_regif.u_puf.u_sram .mem);
      $display("[GLS_PRELOAD][PUF SRAM] loaded real-data noise model from %s", realdata_hex);
    end else begin
      $display("[GLS_PRELOAD][PUF SRAM] no +gls_realdata_hex= given -- PUF SRAM stays at reset content");
    end
  end

  // ---------------------------------------------------------------------
  // IMEM backdoor load: all 10 banks x 4 lanes -- tlul_sram_if_macro_ocd_
  // 10bank's real capacity (vs 7 for top_pd_7bank).
  // ---------------------------------------------------------------------
  string imem_hexdir;
  initial begin
    #1;
    if (!$value$plusargs("gls_imem_hexdir=%s", imem_hexdir)) begin
      $display("[GLS_PRELOAD][IMEM] no +gls_imem_hexdir= given -- IMEM stays at reset (zero) content");
      imem_hexdir = "";
    end
  end

  initial begin
    #2;
    if (imem_hexdir != "") begin
      $readmemh($sformatf("%s/imem_bank0_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[0].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank0_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[0].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank0_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[0].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank0_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[0].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank1_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[1].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank1_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[1].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank1_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[1].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank1_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[1].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank2_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[2].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank2_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[2].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank2_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[2].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank2_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[2].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank3_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[3].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank3_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[3].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank3_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[3].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank3_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[3].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank4_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[4].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank4_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[4].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank4_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[4].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank4_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[4].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank5_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[5].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank5_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[5].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank5_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[5].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank5_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[5].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank6_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[6].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank6_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[6].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank6_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[6].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank6_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[6].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank7_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[7].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank7_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[7].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank7_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[7].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank7_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[7].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank8_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[8].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank8_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[8].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank8_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[8].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank8_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[8].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank9_lane0.hex", imem_hexdir), dut.u_imem.\gen_macros[9].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank9_lane1.hex", imem_hexdir), dut.u_imem.\gen_macros[9].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank9_lane2.hex", imem_hexdir), dut.u_imem.\gen_macros[9].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/imem_bank9_lane3.hex", imem_hexdir), dut.u_imem.\gen_macros[9].u_mem.gen_byte[3].u_macro .mem);
    end
  end

  initial begin
    #3;
    if (imem_hexdir != "")
      $display("[GLS_PRELOAD][IMEM] loaded 10 banks, 4 lanes each from %s", imem_hexdir);
  end

  // ---------------------------------------------------------------------
  // DMEM backdoor load: banks 0-1 x 4 lanes -- tlul_sram_if_macro_ocd_
  // 2bank's real capacity. The packed signed container (64B header +
  // small payload + 40B secp160r1 signature) is under 300 bytes and never
  // leaves bank 0 in practice, but both banks are wired up for headroom.
  // Absent +gls_dmem_hexdir=, DMEM stays at reset (zero) content -- what
  // Stage A (ROM-only validation, no DMEM touched) wants.
  // ---------------------------------------------------------------------
  string dmem_hexdir;
  initial begin
    #1;
    if (!$value$plusargs("gls_dmem_hexdir=%s", dmem_hexdir)) begin
      $display("[GLS_PRELOAD][DMEM] no +gls_dmem_hexdir= given -- DMEM stays at reset (zero) content");
      dmem_hexdir = "";
    end
  end

  initial begin
    #2;
    if (dmem_hexdir != "") begin
      $readmemh($sformatf("%s/dmem_bank0_lane0.hex", dmem_hexdir), dut.u_dmem.\gen_macros[0].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/dmem_bank0_lane1.hex", dmem_hexdir), dut.u_dmem.\gen_macros[0].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/dmem_bank0_lane2.hex", dmem_hexdir), dut.u_dmem.\gen_macros[0].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/dmem_bank0_lane3.hex", dmem_hexdir), dut.u_dmem.\gen_macros[0].u_mem.gen_byte[3].u_macro .mem);
      $readmemh($sformatf("%s/dmem_bank1_lane0.hex", dmem_hexdir), dut.u_dmem.\gen_macros[1].u_mem.gen_byte[0].u_macro .mem);
      $readmemh($sformatf("%s/dmem_bank1_lane1.hex", dmem_hexdir), dut.u_dmem.\gen_macros[1].u_mem.gen_byte[1].u_macro .mem);
      $readmemh($sformatf("%s/dmem_bank1_lane2.hex", dmem_hexdir), dut.u_dmem.\gen_macros[1].u_mem.gen_byte[2].u_macro .mem);
      $readmemh($sformatf("%s/dmem_bank1_lane3.hex", dmem_hexdir), dut.u_dmem.\gen_macros[1].u_mem.gen_byte[3].u_macro .mem);
    end
  end

  initial begin
    #3;
    if (dmem_hexdir != "")
      $display("[GLS_PRELOAD][DMEM] loaded 2 banks, 4 lanes each from %s", dmem_hexdir);
  end

  // ---------------------------------------------------------------------
  // UART line listener (same bit-bang decoder as top_pd_7bank_secboot_gls_tb.sv).
  // ---------------------------------------------------------------------
  localparam int UART_BIT_TICKS = 87;
  typedef enum logic [1:0] {UART_IDLE, UART_START, UART_DATA, UART_STOP} uart_rx_state_e;
  uart_rx_state_e uart_rx_state;
  int  uart_tick_cnt;
  int  uart_bit_idx;
  byte uart_shift;
  string decoded;

  initial decoded = "";

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      uart_rx_state <= UART_IDLE;
      uart_tick_cnt <= 0;
      uart_bit_idx  <= 0;
      uart_shift    <= 8'h00;
    end else begin
      case (uart_rx_state)
        UART_IDLE: begin
          uart_tick_cnt <= 0;
          uart_bit_idx  <= 0;
          if (uart_tx_en && uart_tx == 1'b0) begin
            uart_rx_state <= UART_START;
            uart_tick_cnt <= 1;
          end
        end
        UART_START: begin
          uart_tick_cnt <= uart_tick_cnt + 1;
          if (uart_tick_cnt >= (UART_BIT_TICKS/2)) begin
            if (uart_tx == 1'b0) begin
              uart_rx_state <= UART_DATA;
              uart_tick_cnt <= 0;
              uart_bit_idx  <= 0;
            end else begin
              uart_rx_state <= UART_IDLE;
            end
          end
        end
        UART_DATA: begin
          uart_tick_cnt <= uart_tick_cnt + 1;
          if (uart_tick_cnt >= UART_BIT_TICKS) begin
            uart_tick_cnt <= 0;
            uart_shift[uart_bit_idx] <= uart_tx;
            uart_bit_idx <= uart_bit_idx + 1;
            if (uart_bit_idx == 7) uart_rx_state <= UART_STOP;
          end
        end
        UART_STOP: begin
          uart_tick_cnt <= uart_tick_cnt + 1;
          if (uart_tick_cnt >= UART_BIT_TICKS) begin
            uart_rx_state <= UART_IDLE;
            uart_tick_cnt <= 0;
            $display("[TB][UART_RX] byte=0x%02x ('%s') @%0t",
                     uart_shift,
                     (uart_shift >= 8'h20 && uart_shift <= 8'h7e) ? {uart_shift} : "?",
                     $time);
            decoded = {decoded, string'(uart_shift)};
            // "!" is the sentinel character every stage of this ROM's C
            // code ends its final line with -- same convention the
            // top_pd_7bank secboot tb used.
            if (uart_shift == "!") begin
              $display("");
              $display("[TOP_PD_MIN_SECBOOT] decoded stream:");
              $display("%s", decoded);
              $finish;
            end
          end
        end
      endcase
    end
  end

  initial begin
    rst_n = 0;
    repeat (50) @(posedge clk);
    rst_n = 1;
  end

  // Runtime-tunable timeout (+gls_timeout_ns=). Default was originally
  // 25ms, inherited from top_pd_7bank's secboot tb (UART TX dominates
  // simulated time there, not CPU compute) -- stale for top_pd_min, where
  // every real test has needed far more (60ms-2.7s+) due to the
  // uECC_compute_public_key slowdown investigated separately. Bumped to
  // 500ms as a more realistic default that at least reliably clears PUF
  // read + a meaningful chunk of compute_public_key; still override with
  // +gls_timeout_ns= for anything long-running.
  int unsigned timeout_ns;
  initial begin
    #1;
    if (!$value$plusargs("gls_timeout_ns=%d", timeout_ns)) timeout_ns = 500_000_000;
  end
  initial begin
    #2;
    #(timeout_ns);
    $display("[TOP_PD_MIN_SECBOOT] FAIL: timed out after %0dns. decoded so far: %s", timeout_ns, decoded);
    $display("[DIAG2] total u_imem.tl_i changes=%0d, tl_o changes=%0d", imem_tl_i_changes, imem_tl_o_changes);
    $display("[DIAG_DMEM] total u_dmem.tl_i changes=%0d, tl_o changes=%0d", dmem_tl_i_changes, dmem_tl_o_changes);
    $display("[DIAG3] total u_ibex.clk toggles=%0d (initial clock_en=%b, en_latch=%b)", core_clk_toggle_count, clock_en_val, en_latch_val);
    $display("[DIAG4] total mcycle_lo changes=%0d, final mcycle_lo=%0d", mcycle_change_count, mcycle_lo);
    $display("[DIAG5] total u_data2tl.outstanding_q changes=%0d, u_esram.tl_i changes=%0d, u_esram.tl_o changes=%0d", data_outstanding_changes, esram_tl_i_changes, esram_tl_o_changes);
    $finish;
  end

endmodule
