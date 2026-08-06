// top_pd_7bank_smoke_gls_tb.sv -- new file.
//
// Minimal smoke-test GLS testbench for top_pd_7bank, sibling of
// ../gls/top_pd_puf_smoke_gls_tb.sv (which does this for top_pd_puf's
// mixed 21-bank IMEM / 1KiB ESRAM+DMEM memory plan). top_pd_7bank unifies
// all three memories onto the same tlul_sram_if_macro_ocd_7bank macro
// (7 banks x 1 KiB each = 7 KiB), tiled in an L-shape floorplan and PnR'd
// clean (DRC/LVS/timing signoff all pass on RUN_2026-08-04_17-30-27).
//
// Same rationale as top_pd_puf's own smoke test: the real secure-boot ROM
// image (sw/build/imem.hex, 5053 words) was sized for the old 21-bank IMEM
// (5376-word capacity) and does NOT fit in this design's 7-bank IMEM
// (1792-word capacity) -- so this proves the taped-out netlist's actual
// hardware paths work using the same tiny hand-written program
// (smoke_puf_boot.S, reused unchanged -- the xbar/address map is identical
// since ibex/uart/xbar_tlul_2to5/PUF-glue RTL is byte-for-byte the same as
// top_pd_puf, only the memory macro type changed) that:
//   - fetches/executes entirely from real IMEM bank 0 (tlul_sram_if_macro_
//     ocd_7bank) -- well under its 256-word-per-bank capacity
//   - writes + reads back a test pattern in real ESRAM (same macro type)
//   - triggers the real PUF path (tlul_adapter_reg -> sram_puf_regif ->
//     sram_puf -> real foundry gf180mcu_fd_ip_sram__sram64x8m8wm1 macro),
//     polls done, reads back the first response word
//   - never touches DMEM at all
//
// Only bank 0 of IMEM needs backdoor-loading (not all 7 banks x 4 lanes) --
// this program is a few dozen instructions, comfortably inside one bank.
//
// Backdoor paths below use Verilog ESCAPED IDENTIFIER syntax, confirmed
// directly against the exported pd/macros/top_pd_7bank/top_pd_7bank.nl.v
// and pd/macros/tlul_sram_if_macro_ocd_7bank/tlul_sram_if_macro_ocd_7bank.nl.v:
// same flattening convention as top_pd_puf holds here too --
// ibex/uart/xbar/PUF-glue flattened into escaped wires straight off `dut`,
// and each hard macro's own gen_macros[N].u_mem.gen_byte[M].u_macro
// hierarchy flattened inside its own standalone netlist (banks 0-6 here,
// vs 0-20 for the 21-bank macro).
`timescale 1ns/1ps

module top_pd_7bank_smoke_gls_tb;
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
    $dumpfile("top_pd_7bank_smoke_gls.fst");
    $dumpvars(0, top_pd_7bank_smoke_gls_tb);
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
  // IMEM backdoor load: bank 0 only (4 byte lanes). smoke_puf_boot.S is a
  // few dozen instructions, well under one bank's 256-word capacity, so
  // banks 1-6 stay at their reset (zero) content and are never touched.
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
    end
  end

  initial begin
    #3;
    if (imem_hexdir != "")
      $display("[GLS_PRELOAD][IMEM] loaded bank 0, 4 lanes from %s", imem_hexdir);
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
            // "!" is the last character smoke_puf_boot.S ever sends.
            if (uart_shift == "!") begin
              $display("");
              $display("[TOP_PD_7BANK_SMOKE] decoded stream: %s", decoded);
              $display("[TOP_PD_7BANK_SMOKE] PASS if it reads E (or e if ESRAM readback failed), then P, then 8 hex digits, then !");
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

  // Far shorter timeout than the full secure-boot test -- this program is
  // a few dozen instructions plus one PUF sample cycle.
  initial begin
    #2000000; // 2ms simulated
    $display("[TOP_PD_7BANK_SMOKE] FAIL: timed out. decoded so far: %s", decoded);
    $display("[DIAG2] total u_imem.tl_i changes=%0d, tl_o changes=%0d", imem_tl_i_changes, imem_tl_o_changes);
    $display("[DIAG3] total u_ibex.clk toggles=%0d (initial clock_en=%b, en_latch=%b)", core_clk_toggle_count, clock_en_val, en_latch_val);
    $display("[DIAG4] total mcycle_lo changes=%0d, final mcycle_lo=%0d", mcycle_change_count, mcycle_lo);
    $display("[DIAG5] total u_data2tl.outstanding_q changes=%0d, u_esram.tl_i changes=%0d, u_esram.tl_o changes=%0d", data_outstanding_changes, esram_tl_i_changes, esram_tl_o_changes);
    $finish;
  end

endmodule
