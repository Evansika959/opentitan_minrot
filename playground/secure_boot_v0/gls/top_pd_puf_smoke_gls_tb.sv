// top_pd_puf_smoke_gls_tb.sv -- new file.
//
// Minimal smoke-test GLS testbench for top_pd_puf, sibling of
// ../gls/top_pd_gls_tb.sv (which does this for the older top_pd) and direct
// analog of run_gls_smoke.bash's approach: rather than trying to fit the
// full secure-boot ROM+DMEM payload into the real, size-constrained macros
// (see the DMEM-sizing discussion this file is a response to -- ~309 words
// needed vs 256 available), prove the taped-out netlist's actual hardware
// paths work using a tiny hand-written program (smoke_puf_boot.S) that:
//   - fetches/executes entirely from real IMEM bank 0 (tlul_sram_if_macro_
//     ocd_21bank) -- well under its 256-word-per-bank capacity
//   - writes + reads back a test pattern in real ESRAM (tlul_sram_if_macro)
//   - triggers the real PUF path (tlul_adapter_reg -> sram_puf_regif ->
//     sram_puf -> real foundry gf180mcu_fd_ip_sram__sram64x8m8wm1 macro),
//     polls done, reads back the first response word
//   - never touches DMEM at all -- sidesteps the capacity mismatch
//     entirely instead of trying to trim around it
//
// Only bank 0 of IMEM needs backdoor-loading (not all 21 banks x 4 lanes
// like the full secure-boot smoke would need) -- this program is a few
// dozen instructions, comfortably inside one bank.
//
// Backdoor paths below use Verilog ESCAPED IDENTIFIER syntax
// (`\some.dotted.path .mem`), not plain nested dotted paths. Confirmed
// directly against pd/macros/top_pd_puf/top_pd_puf.nl.v: synthesis
// flattened the entire non-hard-macro portion of top_pd_puf (ibex, uart,
// xbar, u_puf_regif/u_puf) into escaped wire names hanging straight off
// `dut` (u_puf_regif no longer exists as a real instance boundary at
// all), and separately, EACH hard macro's own internal generate hierarchy
// (gen_macros[N]/u_mem/gen_byte[M]/u_macro) is *itself* flattened inside
// that macro's own standalone netlist -- exactly gls_sram_preload.sv's
// already-established convention for tlul_sram_if_macro, confirmed here to
// hold equally for tlul_sram_if_macro_ocd_21bank (see
// pd/macros/tlul_sram_if_macro_ocd_21bank/tlul_sram_if_macro_ocd_21bank.nl.v,
// instances named `\gen_macros[N].u_mem.gen_byte[M].u_macro `). Since an
// escaped identifier is literal text, a genvar can't be spliced into one --
// the 4-lane loop below is unrolled into explicit lines instead of a
// generate-for driving the hierarchical reference itself.
`timescale 1ns/1ps

module top_pd_puf_smoke_gls_tb;
  logic clk;
  logic rst_n;
  logic uart_rx;
  logic uart_tx, uart_tx_en;

  initial clk = 0;
  always #30 clk = ~clk;

  assign uart_rx = 1'b1; // no external UART input needed for this test

  top_pd_puf dut (
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
    $dumpfile("top_pd_puf_smoke_gls.fst");
    $dumpvars(0, top_pd_puf_smoke_gls_tb);
  end

  // TEMP DIAGNOSTIC: plain $display on uart_tx/uart_tx_en/rst_n, unambiguous
  // (the FST/VCD dump showed uart_rx/uart_tx/uart_tx_en sharing one signal
  // code, which is either a real never-toggle situation or a dedup
  // artifact -- this settles it directly, and also confirms clk is really
  // running and rst_n really deasserts).
  initial begin
    $display("[DIAG] t=%0t rst_n=%b uart_tx=%b uart_tx_en=%b", $time, rst_n, uart_tx, uart_tx_en);
    forever begin
      @(uart_tx or uart_tx_en or rst_n);
      $display("[DIAG] t=%0t rst_n=%b uart_tx=%b uart_tx_en=%b", $time, rst_n, uart_tx, uart_tx_en);
    end
  end

  // TEMP DIAGNOSTIC 2: is the CPU issuing ANY bus transaction to IMEM at
  // all? u_imem is a separately-hardened, real module instance (not
  // flattened into dut), so its own tl_i/tl_o ports are plain flat bit
  // vectors ([113:0]/[65:0] per its own netlist) directly reachable via
  // hierarchical reference. Not decoding individual tlul fields here --
  // just checking for ANY activity as a coarse liveness probe.
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

  // TEMP DIAGNOSTIC 3: ibex_top's own internal clock-gate cell
  // (core_clock_gate_i) -- found \u_ibex.clk, \u_ibex.clock_en,
  // \u_ibex.core_clock_gate_i.en_latch as real escaped identifiers in the
  // pure-synthesis netlist. If u_ibex.clk (the gated, core-internal clock)
  // never toggles while the top-level clk_i does, that -- not P&R/CTS --
  // explains why u_imem's own SRAM macros respond fine (they're clocked
  // directly off clk_i) while zero bus activity ever reaches them (the
  // core issuing the requests would be permanently unclocked).
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

  // TEMP DIAGNOSTIC 4: ibex_core's own free-running mcycle counter
  // (u_ibex_core.cs_registers_i.mcycle_counter_i.counter[N], individual
  // escaped-identifier bits since Yosys flattened the vector). This
  // increments every cycle unconditionally regardless of what the pipeline
  // is doing -- if THIS is stuck at 0 while u_ibex.clk is confirmed
  // toggling (DIAG3), the core's sequential logic itself isn't advancing
  // at all (e.g. held in reset), not merely "fetching but getting no
  // response". If it counts normally, the core's basic sequencing works
  // and the dead bus points at something more specific (fetch stage /
  // crossbar), not the whole core being inert.
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

  // TEMP DIAGNOSTIC 5: data-side bus liveness. DIAG2 only ever watched
  // u_imem -- but this program's very first actions after boot are all
  // DATA-side (UART_CTRL store, ESRAM store+load, PUF trigger+poll), and
  // ibex's prefetch buffer can loop over a few already-fetched words
  // (like puf_poll's tiny 3-instruction body) without issuing any NEW
  // instr-bus transaction at all -- so "u_imem quiet" does NOT mean "core
  // stuck", it may just mean "core is correctly spinning on a data-side
  // wait". u_data2tl.outstanding_q (ibex_to_tlul_host's own state,
  // confirmed as a real preserved-name flat wire) toggling proves the data
  // adapter is actually launching/completing bus transactions at all.
  // u_esram is a real, separately-hardened module instance (not
  // flattened), so its tl_i/tl_o are directly reachable exactly like
  // u_imem's already are.
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
  // Optional PUF entropy-source preload. Not required for the mechanism
  // to prove out (the SRAM's reset/zero content still produces a
  // deterministic, readable response), but supported via plusarg in case
  // a real-data model is wanted for this run too.
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
  // banks 1-20 stay at their reset (zero) content and are never touched.
  // ---------------------------------------------------------------------
  string imem_hexdir;
  initial begin
    #1;
    if (!$value$plusargs("gls_imem_hexdir=%s", imem_hexdir)) begin
      $display("[GLS_PRELOAD][IMEM] no +gls_imem_hexdir= given -- IMEM stays at reset (zero) content");
      imem_hexdir = "";
    end
  end

  // Matches split_imem_banks.py's own output naming exactly (reused
  // unmodified -- pointed at the tiny smoke binary instead of a full ROM
  // image, it naturally only writes bank 0's 4 files since the program
  // needs just 1 of the 21 available banks). Unrolled (not a generate-for)
  // because the target is an escaped identifier -- see header comment.
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
  // UART line listener (same bit-bang decoder as top_pd_gls_tb.sv).
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
              $display("[TOP_PD_PUF_SMOKE] decoded stream: %s", decoded);
              $display("[TOP_PD_PUF_SMOKE] PASS if it reads E (or e if ESRAM readback failed), then P, then 8 hex digits, then !");
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
  // a few dozen instructions plus one PUF sample cycle, not a multi-KB
  // boot+verify flow.
  initial begin
    #2000000; // 2ms simulated
    $display("[TOP_PD_PUF_SMOKE] FAIL: timed out. decoded so far: %s", decoded);
    $display("[DIAG2] total u_imem.tl_i changes=%0d, tl_o changes=%0d", imem_tl_i_changes, imem_tl_o_changes);
    $display("[DIAG3] total u_ibex.clk toggles=%0d (initial clock_en=%b, en_latch=%b)", core_clk_toggle_count, clock_en_val, en_latch_val);
    $display("[DIAG4] total mcycle_lo changes=%0d, final mcycle_lo=%0d", mcycle_change_count, mcycle_lo);
    $display("[DIAG5] total u_data2tl.outstanding_q changes=%0d, u_esram.tl_i changes=%0d, u_esram.tl_o changes=%0d", data_outstanding_changes, esram_tl_i_changes, esram_tl_o_changes);
    $finish;
  end

endmodule
