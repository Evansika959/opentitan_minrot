// ibex_glue_instr_only_test_diag_tb.sv -- new file.
//
// Deep diagnostic variant of ibex_glue_instr_only_test_tb.sv: instead of
// just PASS/FAIL on s0, dumps the prefetch-buffer/glue FSM state on every
// change, to find exactly where the fetch pipeline stalls. Only 2 total
// bus transactions were observed over an entire ~21us/350-cycle run in
// the plain test -- this traces WHY.
`timescale 1ns/1ps

module ibex_glue_instr_only_test_diag_tb;
  logic clk;
  logic rst_n;

  initial clk = 0;
  always #30 clk = ~clk;

  ibex_glue_instr_only_test dut (
    .clk_i  (clk),
    .rst_ni (rst_n)
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
    repeat (50) @(posedge clk);
    rst_n = 1;
  end

  // ---------------------------------------------------------------------
  // Bundled FSM status word: any change gets logged with a timestamp.
  // ---------------------------------------------------------------------
  wire        w_instr_rvalid       = dut.instr_rvalid;
  wire        w_outstanding_q      = dut.\u_instr2tl.outstanding_q ;
  wire        w_valid_req_q        = dut.\u_ibex.u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.valid_req_q ;
  wire        w_valid_req_d        = dut.\u_ibex.u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.valid_req_d ;
  wire        w_rdata_outstanding0 = dut.\u_ibex.u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.rdata_outstanding_q[0] ;
  wire        w_rdata_outstanding1 = dut.\u_ibex.u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.rdata_outstanding_q[1] ;
  wire        w_fifo_busy0         = dut.\u_ibex.u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_busy[0] ;
  wire        w_fifo_busy1         = dut.\u_ibex.u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.fifo_busy[1] ;
  wire        w_discard_req_q      = dut.\u_ibex.u_ibex_core.if_stage_i.gen_prefetch_buffer.prefetch_buffer_i.discard_req_q ;
  wire        w_instr_valid_id     = dut.\u_ibex.u_ibex_core.if_stage_i.instr_valid_id_d ;
  wire [31:0] w_instr_addr_dbg     = dut.instr_addr_dbg;
  wire [31:0] w_instr_rdata_dbg    = dut.instr_rdata_dbg;
  wire        w_csr_save_if        = dut.\u_ibex.u_ibex_core.cs_registers_i.csr_save_if_i ;
  wire        w_mcause_q6          = dut.\u_ibex.u_ibex_core.cs_registers_i.mcause_q[6] ;

  // Exact TL-UL field bit-slices at the u_imem macro boundary (real top
  // ports, unaffected by internal glue-module renaming). tl_h2d_t=114b:
  // a_valid[113], a_opcode[112:110], a_address[96:65], d_ready[0].
  // tl_d2h_t=66b: d_valid[65], a_ready[0].
  wire        w_a_valid  = dut.u_imem.tl_i[113];
  wire [2:0]  w_a_opcode = dut.u_imem.tl_i[112:110];
  wire [31:0] w_a_address= dut.u_imem.tl_i[96:65];
  wire        w_d_ready  = dut.u_imem.tl_i[0];
  wire        w_a_ready  = dut.u_imem.tl_o[0];
  wire        w_d_valid  = dut.u_imem.tl_o[65];
  wire        w_imem_clk = dut.u_imem.clk_i;
  wire        w_imem_rst = dut.u_imem.rst_ni;
  wire [3:0]  w_imem_enif= dut.u_imem.en_ifetch_i;

  wire [18:0] status = {w_instr_rvalid, w_outstanding_q, w_valid_req_q, w_valid_req_d,
                         w_rdata_outstanding0, w_rdata_outstanding1, w_fifo_busy0, w_fifo_busy1,
                         w_discard_req_q, w_instr_valid_id, w_csr_save_if, w_mcause_q6,
                         w_a_valid, w_a_ready, w_d_valid, w_d_ready};

  logic [16:0] status_prev;
  int change_count;
  initial begin
    change_count = 0;
    #1;
    status_prev = status;
    $display("[FSM_DIAG] t=%0t initial: rvalid=%b outQ=%b valid_req_q/d=%b/%b rdata_out=%b%b fifo_busy=%b%b discard_q=%b instr_valid_id=%b csr_save_if=%b mcause_q[6]=%b a_valid=%b a_opcode=%03b a_ready=%b d_valid=%b d_ready=%b a_address=%08h addr_dbg=%08h rdata_dbg=%08h",
              $time, w_instr_rvalid, w_outstanding_q, w_valid_req_q, w_valid_req_d,
              w_rdata_outstanding1, w_rdata_outstanding0, w_fifo_busy1, w_fifo_busy0,
              w_discard_req_q, w_instr_valid_id, w_csr_save_if, w_mcause_q6,
              w_a_valid, w_a_opcode, w_a_ready, w_d_valid, w_d_ready, w_a_address, w_instr_addr_dbg, w_instr_rdata_dbg);
    forever begin
      @(status);
      change_count++;
      $display("[FSM_DIAG] t=%0t (#%0d) rvalid=%b outQ=%b valid_req_q/d=%b/%b rdata_out=%b%b fifo_busy=%b%b discard_q=%b instr_valid_id=%b csr_save_if=%b mcause_q[6]=%b a_valid=%b a_opcode=%03b a_ready=%b d_valid=%b d_ready=%b a_address=%08h addr_dbg=%08h rdata_dbg=%08h",
                $time, change_count, w_instr_rvalid, w_outstanding_q, w_valid_req_q, w_valid_req_d,
                w_rdata_outstanding1, w_rdata_outstanding0, w_fifo_busy1, w_fifo_busy0,
                w_discard_req_q, w_instr_valid_id, w_csr_save_if, w_mcause_q6,
                w_a_valid, w_a_opcode, w_a_ready, w_d_valid, w_d_ready, w_a_address, w_instr_addr_dbg, w_instr_rdata_dbg);
    end
  end

  // heartbeat every 200 cycles in case nothing ever changes again
  int cyc;
  initial begin
    cyc = 0;
    forever begin
      repeat (200) @(posedge clk);
      cyc += 200;
      $display("[FSM_DIAG][HEARTBEAT] t=%0t cyc=%0d a_valid=%b a_ready=%b d_valid=%b d_ready=%b a_address=%08h imem_clk=%b imem_rst=%b imem_enif=%04b change_count=%0d", $time, cyc, w_a_valid, w_a_ready, w_d_valid, w_d_ready, w_a_address, w_imem_clk, w_imem_rst, w_imem_enif, change_count);
    end
  end

  initial begin
    @(posedge rst_n);
    repeat (5000) @(posedge clk);
    #1;
    $display("[FSM_DIAG] ===== stopping at t=%0t (5000 cycles after reset release), total status changes=%0d =====", $time, change_count);
    $finish;
  end

endmodule
