`timescale 1ns/1ps

module tb_tlul_sram_if_macro_ocd_multibank;
  import tlul_pkg::*;

  logic clk = 0;
  logic rst_n = 0;
  always #5 clk = ~clk;

  tl_h2d_t tl_h2d;
  tl_d2h_t tl_d2h;

  tlul_sram_if_macro_ocd_multibank #(
    .SramAw(16), .BASE_ADDR(32'h0), .READ_ONLY(1'b0), .NumBanks(4)
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

    while (!tl_d2h.a_ready) begin
      @(posedge clk);
    end

    @(posedge clk);
    tl_h2d.a_valid <= 1'b0;

    while (!tl_d2h.d_valid) begin
      @(posedge clk);
    end
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

    while (!tl_d2h.a_ready) begin
      @(posedge clk);
    end

    @(posedge clk);
    tl_h2d.a_valid <= 1'b0;

    while (!tl_d2h.d_valid) begin
      @(posedge clk);
    end

    data = tl_d2h.d_data;
    err  = tl_d2h.d_error;
  endtask

  logic [31:0] rd;
  logic        rerr;

  // Byte addresses: bank N starts at N * 0x400 (1 KiB per bank).
  localparam logic [31:0] BANK0_WORD0   = 32'h0000_0000;
  localparam logic [31:0] BANK0_WORD255 = 32'h0000_03FC;
  localparam logic [31:0] BANK1_WORD0   = 32'h0000_0400;
  localparam logic [31:0] BANK1_WORD10  = 32'h0000_0428;
  localparam logic [31:0] BANK3_WORD0   = 32'h0000_0C00;
  localparam logic [31:0] BANK3_WORD255 = 32'h0000_0FFC;

  initial begin
    $dumpfile("wave_multibank.fst");
    $dumpvars(0, tb_tlul_sram_if_macro_ocd_multibank);
    tl_h2d = TL_H2D_DEFAULT;
    repeat (3) @(posedge clk);
    rst_n = 1;
    repeat (2) @(posedge clk);

    // --- Bank 0 sanity (same as validated single-bank test) ---
    tl_write(BANK0_WORD0, 32'hDEADBEEF);
    tl_read (BANK0_WORD0, rd, rerr);
    if (rerr || rd !== 32'hDEADBEEF) begin
      $display("FAIL: bank0 word0 expected DEADBEEF, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank0 word0 readback = %08h", rd);

    // --- Bank 1, word 0 ---
    tl_write(BANK1_WORD0, 32'hCAFEF00D);
    tl_read (BANK1_WORD0, rd, rerr);
    if (rerr || rd !== 32'hCAFEF00D) begin
      $display("FAIL: bank1 word0 expected CAFEF00D, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank1 word0 readback = %08h", rd);

    // --- Bank 1, word 10 (arbitrary mid-bank address) ---
    tl_write(BANK1_WORD10, 32'h11223344);
    tl_read (BANK1_WORD10, rd, rerr);
    if (rerr || rd !== 32'h11223344) begin
      $display("FAIL: bank1 word10 expected 11223344, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank1 word10 readback = %08h", rd);

    // --- Bank 3 (last bank), word 0 and word 255 (boundary) ---
    tl_write(BANK3_WORD0, 32'hAAAA5555);
    tl_read (BANK3_WORD0, rd, rerr);
    if (rerr || rd !== 32'hAAAA5555) begin
      $display("FAIL: bank3 word0 expected AAAA5555, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank3 word0 readback = %08h", rd);

    tl_write(BANK3_WORD255, 32'h5A5A5A5A);
    tl_read (BANK3_WORD255, rd, rerr);
    if (rerr || rd !== 32'h5A5A5A5A) begin
      $display("FAIL: bank3 word255 expected 5A5A5A5A, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: bank3 word255 (top of 4KiB window) readback = %08h", rd);

    // --- Cross-bank corruption check: re-read every bank's word0/word10
    //     from earlier to confirm none of the later writes bled across
    //     bank boundaries. ---
    tl_read(BANK0_WORD0, rd, rerr);
    if (rerr || rd !== 32'hDEADBEEF) begin
      $display("FAIL: bank0 word0 corrupted after later writes, got %08h", rd);
      errors++;
    end else $display("PASS: bank0 word0 unaffected by later writes = %08h", rd);

    tl_read(BANK1_WORD0, rd, rerr);
    if (rerr || rd !== 32'hCAFEF00D) begin
      $display("FAIL: bank1 word0 corrupted after later writes, got %08h", rd);
      errors++;
    end else $display("PASS: bank1 word0 unaffected by later writes = %08h", rd);

    tl_read(BANK1_WORD10, rd, rerr);
    if (rerr || rd !== 32'h11223344) begin
      $display("FAIL: bank1 word10 corrupted after later writes, got %08h", rd);
      errors++;
    end else $display("PASS: bank1 word10 unaffected by later writes = %08h", rd);

    if (errors == 0) $display("\n=== ALL MULTIBANK TESTS PASSED (4 banks x 1KiB = 4KiB, OCD macros) ===");
    else              $display("\n=== %0d TEST(S) FAILED ===", errors);

    $finish;
  end

  initial begin
    #200000;
    $display("TIMEOUT: simulation did not complete in time (dut likely stuck waiting on a_ready/d_valid)");
    $finish;
  end

endmodule
