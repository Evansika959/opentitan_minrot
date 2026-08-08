`timescale 1ns/1ps

module tb_tlul_sram_if_macro_ocd_21bank;
  import tlul_pkg::*;

  logic clk = 0;
  logic rst_n = 0;
  always #5 clk = ~clk;

  tl_h2d_t tl_h2d;
  tl_d2h_t tl_d2h;

  tlul_sram_if_macro_ocd_multibank #(
    .SramAw(16), .BASE_ADDR(32'h0), .READ_ONLY(1'b0), .NumBanks(21)
  ) dut (
    .clk_i        (clk),
    .rst_ni       (rst_n),
    .tl_i         (tl_h2d),
    .tl_o         (tl_d2h),
    .en_ifetch_i  (prim_mubi_pkg::MuBi4False)
  );

  int errors = 0;

  task automatic tl_write(input logic [31:0] addr, input logic [31:0] data);
    @(posedge clk);
    tl_h2d.a_valid   <= 1'b1;
    tl_h2d.a_opcode  <= PutFullData;
    tl_h2d.a_address <= addr;
    tl_h2d.a_data    <= data;
    tl_h2d.a_mask    <= 4'hf;
    tl_h2d.a_size    <= 2;
    tl_h2d.d_ready   <= 1'b1;
    while (!tl_d2h.a_ready) @(posedge clk);
    @(posedge clk);
    tl_h2d.a_valid <= 1'b0;
    while (!tl_d2h.d_valid) @(posedge clk);
  endtask

  task automatic tl_read(
    input  logic [31:0] addr,
    output logic [31:0] data,
    output logic        err
  );
    @(posedge clk);
    tl_h2d.a_valid   <= 1'b1;
    tl_h2d.a_opcode  <= Get;
    tl_h2d.a_address <= addr;
    tl_h2d.a_size    <= 2;
    tl_h2d.d_ready   <= 1'b1;
    while (!tl_d2h.a_ready) @(posedge clk);
    @(posedge clk);
    tl_h2d.a_valid <= 1'b0;
    while (!tl_d2h.d_valid) @(posedge clk);
    data = tl_d2h.d_data;
    err  = tl_d2h.d_error;
  endtask

  logic [31:0] rd;
  logic        rerr;

  // Bank N starts at byte address N * 0x400 (1 KiB per bank).
  localparam logic [31:0] BANK0_WORD0    = 32'h0000_0000;
  localparam logic [31:0] BANK1_WORD0    = 32'h0000_0400;
  localparam logic [31:0] BANK10_WORD0   = 32'h0000_2800;
  localparam logic [31:0] BANK20_WORD0   = 32'h0000_5000;  // last bank (0-indexed, 21 total)
  localparam logic [31:0] BANK20_WORD255 = 32'h0000_53FC;  // top word of last bank

  initial begin
    $dumpfile("wave_21bank.fst");
    $dumpvars(0, tb_tlul_sram_if_macro_ocd_21bank);
    tl_h2d = TL_H2D_DEFAULT;
    repeat (3) @(posedge clk);
    rst_n = 1;
    repeat (2) @(posedge clk);

    tl_write(BANK0_WORD0, 32'hDEADBEEF);
    tl_read (BANK0_WORD0, rd, rerr);
    if (rerr || rd !== 32'hDEADBEEF) begin
      $display("FAIL: bank0 word0 expected DEADBEEF, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank0 word0 readback = %08h", rd);

    tl_write(BANK1_WORD0, 32'hCAFEF00D);
    tl_read (BANK1_WORD0, rd, rerr);
    if (rerr || rd !== 32'hCAFEF00D) begin
      $display("FAIL: bank1 word0 expected CAFEF00D, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank1 word0 readback = %08h", rd);

    tl_write(BANK10_WORD0, 32'h10101010);
    tl_read (BANK10_WORD0, rd, rerr);
    if (rerr || rd !== 32'h10101010) begin
      $display("FAIL: bank10 word0 expected 10101010, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank10 word0 readback = %08h", rd);

    tl_write(BANK20_WORD0, 32'hAAAA5555);
    tl_read (BANK20_WORD0, rd, rerr);
    if (rerr || rd !== 32'hAAAA5555) begin
      $display("FAIL: bank20 (last) word0 expected AAAA5555, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank20 (last bank) word0 readback = %08h", rd);

    tl_write(BANK20_WORD255, 32'h5A5A5A5A);
    tl_read (BANK20_WORD255, rd, rerr);
    if (rerr || rd !== 32'h5A5A5A5A) begin
      $display("FAIL: bank20 word255 expected 5A5A5A5A, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank20 (last bank) word255 (top of 21KiB window) readback = %08h", rd);

    // Cross-bank corruption check across the full span.
    tl_read(BANK0_WORD0, rd, rerr);
    if (rerr || rd !== 32'hDEADBEEF) begin
      $display("FAIL: bank0 word0 corrupted, got %08h", rd);
      errors++;
    end else $display("PASS: bank0 word0 unaffected by later writes = %08h", rd);

    tl_read(BANK1_WORD0, rd, rerr);
    if (rerr || rd !== 32'hCAFEF00D) begin
      $display("FAIL: bank1 word0 corrupted, got %08h", rd);
      errors++;
    end else $display("PASS: bank1 word0 unaffected by later writes = %08h", rd);

    tl_read(BANK10_WORD0, rd, rerr);
    if (rerr || rd !== 32'h10101010) begin
      $display("FAIL: bank10 word0 corrupted, got %08h", rd);
      errors++;
    end else $display("PASS: bank10 word0 unaffected by later writes = %08h", rd);

    if (errors == 0) $display("\n=== ALL 21-BANK TESTS PASSED (21 banks x 1KiB = 21KiB, OCD macros) ===");
    else              $display("\n=== %0d TEST(S) FAILED ===", errors);

    $finish;
  end

  initial begin
    #300000;
    $display("TIMEOUT: simulation did not complete in time (dut likely stuck waiting on a_ready/d_valid)");
    $finish;
  end

endmodule
