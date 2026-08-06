// ibex_glue_nomem_test_tb.sv -- new file.
//
// Bisection stage 1.7: runs ibex_glue_nomem_boot.S (bare `lui s0,0x2` +
// infinite loop) through ibex_glue_nomem_test.nl.v (ibex_top +
// ibex_to_tlul_host x2, real tlul_sram_if_macro_ocd_21bank for IMEM, NO
// esram/dmem macro at all -- data glue's tl_i tied to TL_D2H_DEFAULT).
// See ibex_glue_nomem_test.sv's header for what this isolates.
//
// PASS/FAIL: backdoor-probe s0 (x8) directly from the register file, same
// path convention proven in top_pd_puf_lui_test_tb.sv. No ESRAM to read
// back from here.
`timescale 1ns/1ps

module ibex_glue_nomem_test_tb;
  logic clk;
  logic rst_n;

  initial clk = 0;
  always #30 clk = ~clk;

  ibex_glue_nomem_test dut (
    .clk_i  (clk),
    .rst_ni (rst_n)
  );

  // ---------------------------------------------------------------------
  // IMEM backdoor load: bank 0 only.
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

  initial begin
    rst_n = 0;
    repeat (50) @(posedge clk);
    rst_n = 1;
  end

  // ---------------------------------------------------------------------
  // s0 (x8) register-file backdoor probe.
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
  // Instr-bus liveness probe: dut.u_imem is a real macro instance, its
  // top-level tl_i port stays reachable regardless of synth hierarchy mode.
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

  initial begin
    bit pass;
    @(posedge rst_n);
    repeat (300) @(posedge clk);
    #1;
    $display("");
    $display("[IBEX_GLUE_NOMEM] t=%0t final s0 = 0x%08h (expect 0x00002000)", $time, s0_reg);
    $display("[IBEX_GLUE_NOMEM] total s0 changes=%0d", s0_change_count);
    $display("[DIAG2] total u_imem.tl_i changes=%0d", imem_tl_i_changes);
    pass = (s0_reg == 32'h00002000);
    if (pass) $display("[IBEX_GLUE_NOMEM] PASS");
    else      $display("[IBEX_GLUE_NOMEM] FAIL");
    $finish;
  end

endmodule
