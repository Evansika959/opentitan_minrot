// top_pd_puf_gls_tb.sv -- new file.
//
// Gate-level-simulation (GLS) testbench for the taped-out top_pd_puf
// netlist. Sibling of ../gls/top_pd_gls_tb.sv (which does this for the
// older, no-PUF top_pd) -- same pin-level-only DUT visibility (clk_i/
// rst_ni/uart_rx_i/uart_tx_o/uart_tx_en_o), same bit-bang UART decoder.
//
// The RTL reference this is meant to match is sim_macro21
// (puf_secure_boot_macro21_tb.sv, xinting:puf:puf_secure_boot_top) --
// see secure_boot_v0_puf_gls.core's header for the important caveat that
// sim_macro21's DUT keeps DMEM idealized, while top_pd_puf's DMEM is a real
// macro. Pass condition (copied from puf_secure_boot_macro21_tb.sv, which
// is itself the pass condition the compiled ROM/payload actually prints):
// UART stream contains "Payload: verified boot OK".
//
// Preloading, three different memories, three different mechanisms:
//   - IMEM (u_imem, tlul_sram_if_macro_ocd_21bank, 84 real macro instances):
//     new backdoor-load generate loop below, mirroring
//     puf_secure_boot_macro21_tb.sv's own approach exactly (same
//     gen_macros[bk].u_mem.gen_byte[ln].u_macro hierarchy, since that
//     macro's own internal structure is unchanged by hardening -- confirmed
//     directly against this exact netlist's ODB during PD bring-up).
//     Populated bank count (IMEM_POPULATED_BANKS) matches whatever
//     split_imem_banks.py produced for the actual compiled ROM -- verify
//     this against the real bank count before running (macro21's own ROM
//     build populated banks 0-11 of 21; this build may differ slightly).
//   - ESRAM (u_esram, tlul_sram_if_macro): no preload -- reuses
//     ../gls/gls_sram_preload.sv unmodified (bound into every
//     tlul_sram_if_macro instance already); ESRAM starts empty on purpose,
//     the ROM's own copy_payload() writes the verified payload into it at
//     runtime, same as every prior real-ESRAM demo in this project.
//   - DMEM (u_dmem, tlul_sram_if_macro): also handled by
//     gls_sram_preload.sv unmodified -- pass +gls_dmem_hex=<combined.dmem.hex>
//     and it self-selects via its own %m path match on "u_dmem".
//   - PUF SRAM (u_puf_regif.u_puf.u_sram, gf180mcu_fd_ip_sram__sram64x8m8wm1):
//     new preload below, straight $readmemh into .mem, same as
//     puf_secure_boot_macro21_tb.sv does at RTL. VERIFY THIS PATH FIRST --
//     harden_block.sh passes --keep-hierarchy to slang project-wide (added
//     earlier for an unrelated inout-port-inlining bug), so this exact RTL
//     hierarchy is likely preserved in top_pd_puf.nl.v, but this was never
//     confirmed for THIS specific nested path before -- if elaboration
//     fails to find it, grep top_pd_puf.nl.v for "u_puf_regif" to find its
//     actual post-synthesis name and fix the path below.
`timescale 1ns/1ps

module top_pd_puf_gls_tb;
  logic clk;
  logic rst_n;
  logic uart_rx;
  logic uart_tx, uart_tx_en;

  initial clk = 0;
  always #30 clk = ~clk;

  // No external UART input needed for this test (ROM boots + verifies +
  // jumps on its own; matches puf_secure_boot_macro21_tb.sv, which drives
  // no uart_rx either -- tie it idle/high).
  assign uart_rx = 1'b1;

  top_pd_puf dut (
    .clk_i        (clk),
    .rst_ni       (rst_n),
    .uart_rx_i    (uart_rx),
    .uart_tx_o    (uart_tx),
    .uart_tx_en_o (uart_tx_en)
  );

  // ---------------------------------------------------------------------
  // PUF entropy source preload (real foundry SRAM primitive's own noise
  // model, NOT boot content -- see puf_secure_boot_macro21_tb.sv, same
  // mechanism).
  // ---------------------------------------------------------------------
  initial begin
    string realdata_hex;
    #1;
    if ($value$plusargs("gls_realdata_hex=%s", realdata_hex)) begin
      $readmemh(realdata_hex, dut.u_puf_regif.u_puf.u_sram.mem);
      $display("[GLS_PRELOAD][PUF SRAM] loaded real-data noise model from %s", realdata_hex);
    end else begin
      $display("[GLS_PRELOAD][PUF SRAM] no +gls_realdata_hex= given -- PUF SRAM stays at reset content");
    end
  end

  // ---------------------------------------------------------------------
  // IMEM backdoor load: 84 real macro instances (21 banks x 4 byte lanes).
  // Only the populated banks need loading -- unpopulated ones stay at the
  // macro model's own zero reset, same as puf_secure_boot_macro21_tb.sv.
  // Directory + populated-bank-count come from split_imem_banks.py's own
  // output (see run_secure_boot_macro21_demo.bash step 5 for the reference
  // invocation) via plusarg rather than hardcoded/sed-substituted paths,
  // matching top_pd_gls_tb's own plusarg convention instead of
  // puf_secure_boot_macro21_tb.sv's build-time sed substitution.
  // ---------------------------------------------------------------------
  localparam int IMEM_POPULATED_BANKS = 12; // VERIFY against actual split_imem_banks.py output
  string imem_bankdir;
  initial begin
    #1;
    if (!$value$plusargs("gls_imem_bankdir=%s", imem_bankdir)) begin
      $display("[GLS_PRELOAD][IMEM] no +gls_imem_bankdir= given -- IMEM stays at reset (zero) content");
      imem_bankdir = "";
    end
  end

  generate
    for (genvar bk = 0; bk < IMEM_POPULATED_BANKS; bk++) begin : gen_imem_ld_bank
      for (genvar ln = 0; ln < 4; ln++) begin : gen_imem_ld_lane
        initial begin
          #2; // after imem_bankdir is resolved above
          if (imem_bankdir != "") begin
            $readmemh(
              $sformatf("%s/imem_bank%0d_lane%0d.hex", imem_bankdir, bk, ln),
              dut.u_imem.gen_macros[bk].u_mem.gen_byte[ln].u_macro.mem
            );
          end
        end
      end
    end
  endgenerate

  initial begin
    #3;
    if (imem_bankdir != "")
      $display("[GLS_PRELOAD][IMEM] loaded %0d banks x 4 lanes from %s", IMEM_POPULATED_BANKS, imem_bankdir);
  end

  // Lightweight progress heartbeat -- every 5ms simulated (same as
  // puf_secure_boot_macro21_tb.sv; this scale of real-macro-instance count
  // is slow, "hung" is usually just "hasn't heartbeat-ed recently", not a
  // real failure -- check for forward progress before assuming a hang).
  initial begin
    forever begin
      #5000000;
      $display("[HEARTBEAT] t=%0t", $time);
    end
  end

  // ---------------------------------------------------------------------
  // UART line listener: decode uart_tx into bytes (same bit-bang decoder
  // as top_pd_gls_tb.sv / puf_secure_boot_macro21_tb.sv -- same uart
  // peripheral, same ~115200 baud / ~87-cycle-per-bit assumption).
  // ---------------------------------------------------------------------
  localparam int UART_BIT_TICKS = 87;
  typedef enum logic [1:0] {UART_IDLE, UART_START, UART_DATA, UART_STOP} uart_rx_state_e;
  uart_rx_state_e uart_rx_state;
  int    uart_tick_cnt;
  int    uart_bit_idx;
  byte   uart_shift;
  int    bytes_seen;
  string decoded;
  bit    pass_seen;

  initial begin
    bytes_seen = 0;
    decoded = "";
    pass_seen = 0;
  end

  function automatic bit contains(string s, string pat);
    int n, m, k;
    bit found;
    n = s.len();
    m = pat.len();
    found = 0;
    if (m != 0 && m <= n) begin
      for (k = 0; k <= n - m; k++) begin
        if (!found && s.substr(k, k + m - 1) == pat) found = 1;
      end
    end
    contains = found;
  endfunction

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
            $write("%c", uart_shift);
            decoded = {decoded, string'(uart_shift)};
            bytes_seen <= bytes_seen + 1;
            if (!pass_seen && contains(decoded, "Payload: verified boot OK")) begin
              pass_seen <= 1;
              $display("");
              $display("[TOP_PD_PUF_GLS] PASS: taped-out netlist's real 21-bank IMEM fetched/ran the ROM, verified the PUF-signed payload, copied it into real ESRAM, and jumped to it.");
              $display("[TOP_PD_PUF_GLS] TIMING: t=%0t", $time);
              $finish;
            end
          end
        end
      endcase
    end
  end

  initial begin
    rst_n = 0;
    repeat (5) @(posedge clk);
    rst_n = 1;
  end

  // Generous timeout, matching puf_secure_boot_macro21_tb.sv's own budget
  // for this scale of real-macro-instance count (~88 there; this design adds
  // the real DMEM macro on top, so if anything this needs MORE headroom,
  // not less).
  initial begin
    #20000000000;
    $display("");
    if (contains(decoded, "VERIFY FAIL"))
      $display("[TOP_PD_PUF_GLS] FAIL: ROM rejected the image's signature.");
    else if (contains(decoded, "ROM: BAD") || contains(decoded, "ROM: PAYLOAD") ||
             contains(decoded, "ROM: SIG") || contains(decoded, "ROM: LOAD") ||
             contains(decoded, "ROM: ENTRY"))
      $display("[TOP_PD_PUF_GLS] FAIL: header verification rejected the image.");
    else
      $display("[TOP_PD_PUF_GLS] FAIL: no result seen (%0d bytes received) -- timed out or crashed.", bytes_seen);
    $finish;
  end

endmodule
