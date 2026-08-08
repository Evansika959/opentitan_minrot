// top_pd_puf_lui_test_tb.sv -- new file.
//
// Runs top_pd_puf_lui_test_boot.S (5-immediate LUI diagnostic, same values
// as ibex_lui_bitpattern2_boot.S) through the REAL top_pd_puf netlist --
// real IMEM fetch, real ibex, real xbar, real ESRAM -- and verifies by
// backdoor-reading ESRAM's own storage array directly, bypassing UART/PUF
// entirely so this stays isolated to exactly the ibex+xbar+ESRAM path,
// mirroring the scope of the standalone ibex_top macro test but through
// whichever top_pd_puf-level netlist stage it's pointed at (06synth /
// 19preplace / 35postcts / final).
//
// u_esram is a real, separately-hardened module instance (not flattened),
// so its internal 4-byte-lane SRAM storage is reachable exactly the way
// gls_sram_preload.sv already backdoor-WRITES it -- this does the reverse
// (backdoor READ) after the program has run.
`timescale 1ns/1ps

module top_pd_puf_lui_test_tb;
  logic clk;
  logic rst_n;
  logic uart_rx;
  logic uart_tx, uart_tx_en;

  initial clk = 0;
  always #30 clk = ~clk;

  assign uart_rx = 1'b1;

  top_pd_puf dut (
    .clk_i        (clk),
    .rst_ni       (rst_n),
    .uart_rx_i    (uart_rx),
    .uart_tx_o    (uart_tx),
    .uart_tx_en_o (uart_tx_en)
  );

  // ---------------------------------------------------------------------
  // IMEM backdoor load: bank 0 only, same mechanism/paths as
  // top_pd_puf_smoke_gls_tb.sv.
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
      $display("[GLS_PRELOAD][IMEM] loaded bank 0, 4 lanes from %s", imem_hexdir);
    end
  end

  // ---------------------------------------------------------------------
  // ESRAM backdoor read: reconstruct 32-bit words from the 4 byte-lane
  // SRAM arrays, same addressing gls_sram_preload.sv uses for its WRITE.
  // ---------------------------------------------------------------------
  function automatic logic [31:0] esram_word(int idx);
    esram_word = {dut.u_esram.\u_mem.gen_byte[3].u_macro .mem[idx],
                  dut.u_esram.\u_mem.gen_byte[2].u_macro .mem[idx],
                  dut.u_esram.\u_mem.gen_byte[1].u_macro .mem[idx],
                  dut.u_esram.\u_mem.gen_byte[0].u_macro .mem[idx]};
  endfunction

  initial begin
    rst_n = 0;
    repeat (50) @(posedge clk);
    rst_n = 1;
  end

  // ---------------------------------------------------------------------
  // TEMP DIAGNOSTIC: direct probe on register x8 (s0)'s own register-file
  // storage flops. In the standalone ibex_top macro's post-PnR netlist,
  // `lui s0, 0x10` (with 5 NOPs of margin before use) never actually
  // landed -- s0 read back as 0 in every test, regardless of delay. This
  // checks whether the SAME failure exists in top_pd_puf's own (separately
  // synthesized, flattened) ibex, independent of whatever else might also
  // be wrong -- confirmed as a real, preserved signal name (160 references
  // in this exact netlist stage) before wiring it in.
  // ---------------------------------------------------------------------
  wire [31:0] s0_reg;
  assign s0_reg[0]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[0] ;
  assign s0_reg[1]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[1] ;
  assign s0_reg[2]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[2] ;
  assign s0_reg[3]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[3] ;
  assign s0_reg[4]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[4] ;
  assign s0_reg[5]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[5] ;
  assign s0_reg[6]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[6] ;
  assign s0_reg[7]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[7] ;
  assign s0_reg[8]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[8] ;
  assign s0_reg[9]  = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[9] ;
  assign s0_reg[10] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[10] ;
  assign s0_reg[11] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[11] ;
  assign s0_reg[12] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[12] ;
  assign s0_reg[13] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[13] ;
  assign s0_reg[14] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[14] ;
  assign s0_reg[15] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[15] ;
  assign s0_reg[16] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[16] ;
  assign s0_reg[17] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[17] ;
  assign s0_reg[18] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[18] ;
  assign s0_reg[19] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[19] ;
  assign s0_reg[20] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[20] ;
  assign s0_reg[21] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[21] ;
  assign s0_reg[22] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[22] ;
  assign s0_reg[23] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[23] ;
  assign s0_reg[24] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[24] ;
  assign s0_reg[25] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[25] ;
  assign s0_reg[26] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[26] ;
  assign s0_reg[27] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[27] ;
  assign s0_reg[28] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[28] ;
  assign s0_reg[29] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[29] ;
  assign s0_reg[30] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[30] ;
  assign s0_reg[31] = dut.\u_ibex.gen_regfile_ff.register_file_i.g_rf_flops[8].rf_reg_q[31] ;

  logic [31:0] s0_reg_prev;
  int s0_change_count;
  initial begin
    s0_change_count = 0;
    #1;
    s0_reg_prev = s0_reg;
    $display("[S0_DIAG] t=%0t initial s0=0x%08h", $time, s0_reg);
    forever begin
      @(s0_reg);
      s0_change_count++;
      $display("[S0_DIAG] t=%0t s0 changed (#%0d): 0x%08h -> 0x%08h", $time, s0_change_count, s0_reg_prev, s0_reg);
      s0_reg_prev = s0_reg;
    end
  end

  // ---------------------------------------------------------------------
  // TEMP DIAGNOSTIC: same liveness probes as top_pd_puf_smoke_gls_tb.sv --
  // instr-bus activity count and ibex's own free-running mcycle counter.
  // Distinguishes "CPU never runs at this stage" from "CPU runs but the
  // data-side write to ESRAM specifically never lands".
  // ---------------------------------------------------------------------
  logic [113:0] imem_tl_i_prev;
  int imem_tl_i_changes;
  initial begin
    imem_tl_i_changes = 0;
    imem_tl_i_prev = dut.u_imem.tl_i;
    forever begin
      @(dut.u_imem.tl_i);
      if (dut.u_imem.tl_i !== imem_tl_i_prev) begin
        imem_tl_i_changes++;
        if (imem_tl_i_changes <= 10)
          $display("[DIAG2] t=%0t u_imem.tl_i changed (#%0d): %h", $time, imem_tl_i_changes, dut.u_imem.tl_i);
        imem_tl_i_prev = dut.u_imem.tl_i;
      end
    end
  end

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
  int mcycle_change_count;
  logic [19:0] mcycle_lo_prev;
  initial begin
    mcycle_change_count = 0;
    #1;
    mcycle_lo_prev = mcycle_lo;
    forever begin
      @(mcycle_lo);
      mcycle_change_count++;
      mcycle_lo_prev = mcycle_lo;
    end
  end

  initial begin
    logic [31:0] w0, w1, w2, w3, w4, w5;
    bit pass;
    @(posedge rst_n);
    wait (esram_word(5) == 32'h1);
    @(posedge clk); #1;
    w0 = esram_word(0);
    w1 = esram_word(1);
    w2 = esram_word(2);
    w3 = esram_word(3);
    w4 = esram_word(4);
    w5 = esram_word(5);
    $display("");
    $display("[TOP_PD_PUF_LUI] t=%0t ESRAM+0x00 (delay=0, imm=0x00001) = 0x%08h (expect 0x00001000)", $time, w0);
    $display("[TOP_PD_PUF_LUI] ESRAM+0x04 (delay=1, imm=0x00010) = 0x%08h (expect 0x00010000)", w1);
    $display("[TOP_PD_PUF_LUI] ESRAM+0x08 (delay=2, imm=0xfffef) = 0x%08h (expect 0xfffef000)", w2);
    $display("[TOP_PD_PUF_LUI] ESRAM+0x0c (delay=3, imm=0x00000) = 0x%08h (expect 0x00000000)", w3);
    $display("[TOP_PD_PUF_LUI] ESRAM+0x10 (delay=4, imm=0xfffff) = 0x%08h (expect 0xfffff000)", w4);
    $display("[TOP_PD_PUF_LUI] ESRAM+0x14 (done marker)         = 0x%08h (expect 0x00000001)", w5);
    pass = (w0 == 32'h00001000) && (w1 == 32'h00010000) && (w2 == 32'hfffef000) &&
           (w3 == 32'h00000000) && (w4 == 32'hfffff000);
    if (pass) $display("[TOP_PD_PUF_LUI] PASS");
    else      $display("[TOP_PD_PUF_LUI] FAIL");
    $finish;
  end

  initial begin
    #4000000;
    $display("[TOP_PD_PUF_LUI] FAIL: timed out -- done marker (ESRAM+0x14) never written.");
    $display("[TOP_PD_PUF_LUI] ESRAM+0x00 = 0x%08h", esram_word(0));
    $display("[TOP_PD_PUF_LUI] ESRAM+0x04 = 0x%08h", esram_word(1));
    $display("[TOP_PD_PUF_LUI] ESRAM+0x08 = 0x%08h", esram_word(2));
    $display("[TOP_PD_PUF_LUI] ESRAM+0x0c = 0x%08h", esram_word(3));
    $display("[TOP_PD_PUF_LUI] ESRAM+0x10 = 0x%08h", esram_word(4));
    $display("[DIAG2] total u_imem.tl_i changes=%0d", imem_tl_i_changes);
    $display("[DIAG4] total mcycle_lo changes=%0d, final mcycle_lo=%0d", mcycle_change_count, mcycle_lo);
    $display("[S0_DIAG] total s0 changes=%0d, final s0=0x%08h (expect 0x00010000)", s0_change_count, s0_reg);
    $finish;
  end

endmodule
