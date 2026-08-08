// top_pd_7bank_secboot_gls_tb.sv -- new file, forked from the proven-good
// top_pd_7bank_smoke_gls_tb.sv (that file is left untouched as the known-
// good regression reference; do not merge changes back into it).
//
// GLS testbench for the real-crypto secure-boot + PUF demo on top_pd_7bank.
// Two differences from the smoke tb this was forked from:
//   1. IMEM backdoor-load now unrolls all 7 banks x 4 lanes (28 $readmemh
//      calls), not just bank 0 -- a compiled-C ROM with real SHA256/ECDSA
//      (secp160r1) is ~1.6K words, several times bigger than the smoke
//      test's few-dozen-instruction hand-written program, and spans
//      multiple banks.
//   2. DMEM backdoor-load added (bank 0 only -- the packed signed container
//      is small and never leaves bank 0), guarded by a new +gls_dmem_hex=
//      plusarg. Absent that arg, DMEM stays at reset (zero) content, same
//      as this file's Stage-A use (ROM-only validation, no DMEM touched).
//
// Backdoor paths use the same Verilog ESCAPED IDENTIFIER syntax as the
// smoke tb, confirmed against the same exported netlists: each hard
// macro's own gen_macros[N].u_mem.gen_byte[M].u_macro hierarchy flattened
// inside its own standalone netlist file (banks 0-6, 4 lanes each), same
// structure for u_imem/u_esram/u_dmem (they're all the same macro type).
`timescale 1ns/1ps

module top_pd_7bank_secboot_gls_tb;
  logic clk;
  logic rst_n;
  logic uart_rx;
  logic uart_tx, uart_tx_en;

  initial clk = 0;
  always #30 clk = ~clk;

  assign uart_rx = 1'b1; // no external UART input needed for this test

  top_pd_7bank dut (
    .clk_i        (clk),
    .rst_ni       (rst_n),
    .uart_rx_i    (uart_rx),
    .uart_tx_o    (uart_tx),
    .uart_tx_en_o (uart_tx_en)
  );

  // ---------------------------------------------------------------------
  // Waveform dump. --trace-fst at compile time is not sufficient on its
  // own in Verilator's --binary mode -- the auto-generated main() only
  // calls contextp->traceEverOn(true), it never opens or dumps a trace
  // file. $dumpfile/$dumpvars is what Verilator actually translates into
  // real FST dump calls; without this, --trace-fst silently produces no
  // file at all.
  // ---------------------------------------------------------------------
  initial begin
    $dumpfile("top_pd_7bank_secboot_gls.fst");
    $dumpvars(0, top_pd_7bank_secboot_gls_tb);
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

  // DIAG2: is the CPU issuing ANY bus transaction to IMEM at all? u_imem
  // is a separately-hardened, real module instance (not flattened into
  // dut), so its own tl_i/tl_o ports are plain flat bit vectors
  // ([113:0]/[65:0]) directly reachable via hierarchical reference.
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
  // tl_i/tl_o -- u_esram is real, separately-hardened, directly reachable).
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
  // IMEM backdoor load: all 7 banks x 4 lanes. The compiled-C ROM is big
  // enough to span every bank, unlike the smoke test's hand-written
  // program (which only ever needed bank 0).
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
    end
  end

  initial begin
    #3;
    if (imem_hexdir != "")
      $display("[GLS_PRELOAD][IMEM] loaded 7 banks, 4 lanes each from %s", imem_hexdir);
  end

  // ---------------------------------------------------------------------
  // DMEM backdoor load: bank 0 only. The packed signed container (64B
  // header + small payload + 40B secp160r1 signature) never leaves bank 0.
  // Absent +gls_dmem_hex=, DMEM stays at reset (zero) content -- which is
  // exactly what Stage A (ROM-only validation, no DMEM touched) wants.
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
    end
  end

  initial begin
    #3;
    if (dmem_hexdir != "")
      $display("[GLS_PRELOAD][DMEM] loaded bank 0, 4 lanes from %s", dmem_hexdir);
  end

  // ---------------------------------------------------------------------
  // UART line listener (same bit-bang decoder as top_pd_puf_smoke_gls_tb.sv).
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
            // code ends its final line with (see rom_7bank_stageA.c /
            // rom_secure_boot_7bank.c), same convention the smoke test
            // used, so this exit trigger needs no change between stages.
            if (uart_shift == "!") begin
              $display("");
              $display("[TOP_PD_7BANK_SECBOOT] decoded stream:");
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

  // Runtime-tunable timeout (+gls_timeout_ns=), default 25ms. UART TX
  // dominates simulated time here (~52us/byte at 115200 baud measured
  // against this tb's clock; CPU compute -- PUF sample, uECC math -- is
  // negligible next to that), so the budget scales with how much text a
  // given ROM stage prints, not with how much it computes. Deliberately
  // NOT the 20-second timeout the earlier top_pd_puf secure-boot attempt
  // used -- that one burned ~49 hours of wall-clock time hitting it on a
  // silent failure. Pick the smallest value that comfortably covers this
  // stage's actual expected UART output instead of a large fixed guess.
  int unsigned timeout_ns;
  initial begin
    #1;
    if (!$value$plusargs("gls_timeout_ns=%d", timeout_ns)) timeout_ns = 25_000_000;
  end
  initial begin
    #2;
    #(timeout_ns); // timescale is 1ns/1ps -- same unit convention as the original #2000000 literal
    $display("[TOP_PD_7BANK_SECBOOT] FAIL: timed out after %0dns. decoded so far: %s", timeout_ns, decoded);
    $display("[DIAG2] total u_imem.tl_i changes=%0d, tl_o changes=%0d", imem_tl_i_changes, imem_tl_o_changes);
    $display("[DIAG3] total u_ibex.clk toggles=%0d (initial clock_en=%b, en_latch=%b)", core_clk_toggle_count, clock_en_val, en_latch_val);
    $display("[DIAG4] total mcycle_lo changes=%0d, final mcycle_lo=%0d", mcycle_change_count, mcycle_lo);
    $display("[DIAG5] total u_data2tl.outstanding_q changes=%0d, u_esram.tl_i changes=%0d, u_esram.tl_o changes=%0d", data_outstanding_changes, esram_tl_i_changes, esram_tl_o_changes);
    $finish;
  end

endmodule
