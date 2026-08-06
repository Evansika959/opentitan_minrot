// ibex_glue_instr_only_fedelay_test_tb.sv -- new file.
//
// Confirmation test: identical setup to ibex_glue_instr_only_test_diag_tb
// (same boot program, same probes), except fetch_enable_i is now driven
// by the testbench instead of a hardwired constant -- held at
// ibex_pkg::IbexMuBiOff for FETCH_DELAY_CYCLES after reset release, then
// switched to IbexMuBiOn. If the real macro's request FIFOs only needed
// a few idle cycles post-reset (the same workaround
// tlul_sram_if_macro_solo_gls_tb.sv already used), s0 should now get
// written correctly.
`timescale 1ns/1ps

module ibex_glue_instr_only_fedelay_test_tb;
  localparam logic [3:0] IBEX_MUBI_ON  = 4'b0101;
  localparam logic [3:0] IBEX_MUBI_OFF = 4'b1010;
  localparam int FETCH_DELAY_CYCLES = 10;

  logic clk;
  logic rst_n;
  logic [3:0] fetch_enable;

  initial clk = 0;
  always #30 clk = ~clk;

  ibex_glue_instr_only_fedelay_test dut (
    .clk_i          (clk),
    .rst_ni         (rst_n),
    .fetch_enable_i (fetch_enable)
  );

  string imem_hexdir;
  initial begin
    #1;
    if (!$value$plusargs("gls_imem_hexdir=%s", imem_hexdir)) imem_hexdir = "";
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
    fetch_enable = IBEX_MUBI_OFF;
    repeat (50) @(posedge clk);
    rst_n = 1;
    repeat (FETCH_DELAY_CYCLES) @(posedge clk);
    fetch_enable = IBEX_MUBI_ON;
    $display("[FEDELAY] t=%0t fetch_enable_i switched ON, %0d cycles after reset release", $time, FETCH_DELAY_CYCLES);
  end

  // ---------------------------------------------------------------------
  // Same TL-UL field probes as the diag testbench, at the u_imem boundary.
  // ---------------------------------------------------------------------
  wire        w_a_valid  = dut.u_imem.tl_i[113];
  wire [2:0]  w_a_opcode = dut.u_imem.tl_i[112:110];
  wire [31:0] w_a_address= dut.u_imem.tl_i[96:65];
  wire        w_a_ready  = dut.u_imem.tl_o[0];
  wire        w_d_valid  = dut.u_imem.tl_o[65];

  wire [4:0] status = {w_a_valid, w_a_ready, w_d_valid};
  int change_count;
  initial begin
    change_count = 0;
    forever begin
      @(status);
      change_count++;
      if (change_count <= 40)
        $display("[FEDELAY_DIAG] t=%0t (#%0d) a_valid=%b a_opcode=%03b a_ready=%b d_valid=%b a_address=%08h",
                  $time, change_count, w_a_valid, w_a_opcode, w_a_ready, w_d_valid, w_a_address);
    end
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

  initial begin
    bit pass;
    @(posedge rst_n);
    repeat (500) @(posedge clk);
    #1;
    $display("");
    $display("[IBEX_FEDELAY] t=%0t final s0 = 0x%08h (expect 0x00002000)", $time, s0_reg);
    $display("[IBEX_FEDELAY] total a_valid/a_ready/d_valid changes=%0d", change_count);
    pass = (s0_reg == 32'h00002000);
    if (pass) $display("[IBEX_FEDELAY] PASS");
    else      $display("[IBEX_FEDELAY] FAIL");
    $finish;
  end

endmodule
