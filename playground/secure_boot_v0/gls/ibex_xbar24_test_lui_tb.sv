// ibex_xbar24_test_lui_tb.sv -- new file.
//
// Bisection stage 2: runs top_pd_puf_lui_test_boot.S through
// ibex_xbar_test.nl.v (ibex_top + ibex_to_tlul_host + xbar_tlul_2to5,
// synthesized together, no uart/PUF/DMEM) with the real, already-proven
// tlul_sram_if_macro_ocd_21bank/tlul_sram_if_macro netlists stitched in
// for the blackboxed ROM/ESRAM ports. Verifies by backdoor-reading ESRAM
// directly (u_esram is a real, separately-hardened -- never flattened --
// module instance regardless of SYNTH_HIERARCHY_MODE, so this works the
// same way in every variant of this test).
//
// NOTE: the internal s0/mcycle register-file probes used in earlier
// variants of this test are deliberately NOT included here -- with
// SYNTH_HIERARCHY_MODE=keep, Yosys emits a genuinely separate Verilog
// `module`/`endmodule` block per RTL submodule instance (mangled type
// names like `ibex_register_file_ff$ibex_xbar_test.u_ibex.gen_regfile_ff.
// register_file_i`), not one flattened module with decorative hierarchical
// wire names -- so the old single flat escaped-identifier probe paths no
// longer resolve. Not needed for this test anyway: PASS/FAIL is fully
// determined by the ESRAM backdoor read below.
`timescale 1ns/1ps

module ibex_xbar24_test_lui_tb;
  logic clk;
  logic rst_n;

  initial clk = 0;
  always #30 clk = ~clk;

  ibex_xbar24_test dut (
    .clk_i  (clk),
    .rst_ni (rst_n)
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
  // Instr-bus liveness probe: dut.u_imem is a real, separately-hardened
  // module instance (blackboxed macro), so its top-level tl_i port stays
  // reachable exactly the same way regardless of SYNTH_HIERARCHY_MODE.
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
    $finish;
  end

endmodule
