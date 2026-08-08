`timescale 1ns/1ps

module tb_tlul_sram_if_macro;
  import tlul_pkg::*;

  logic clk = 0;
  logic rst_n = 0;
  always #5 clk = ~clk;

  tl_h2d_t tl_h2d;
  tl_d2h_t tl_d2h;

  tlul_sram_if_macro #(
    .SramAw(16), .BASE_ADDR(32'h0), .READ_ONLY(1'b0)
  ) dut (
    .clk_i        (clk),
    .rst_ni       (rst_n),
    .tl_i         (tl_h2d),
    .tl_o         (tl_d2h),
    .en_ifetch_i  (prim_mubi_pkg::MuBi4False)
  );

  int errors = 0;

  // Minimal TL-UL host: issue one a-channel request, wait for d-channel response.
  // Drive a_valid/a_* with non-blocking assignments inside a clocked process,
  // so transitions are cleanly aligned to the clock edge instead of racing
  // combinational logic in the same simulation delta (this was the bug in
  // both earlier attempts: blocking assignments caused either a sub-cycle
  // glitch or an accidental double-issue of the same request).
// Write Task
task automatic tl_write(input logic [31:0] addr, input logic [31:0] data);
  @(posedge clk);
  tl_h2d.a_valid   <= 1'b1;
  tl_h2d.a_opcode  <= PutFullData;
  tl_h2d.a_address <= addr;
  tl_h2d.a_data    <= data;
  tl_h2d.a_mask    <= 4'hf;
  tl_h2d.a_size    <= 2;
  tl_h2d.d_ready   <= 1'b1;

  // Wait until a_ready is sampled HIGH
  while (!tl_d2h.a_ready) begin
    @(posedge clk);
  end

  // Sample d_valid state on the current clock edge before deasserting a_valid on the next
  @(posedge clk);
  tl_h2d.a_valid <= 1'b0;

  // If d_valid was not already asserted, wait for it
  while (!tl_d2h.d_valid) begin
    @(posedge clk);
  end
endtask

// Read Task
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

  // Wait until a_ready is sampled HIGH
  while (!tl_d2h.a_ready) begin
    @(posedge clk);
  end

  @(posedge clk);
  tl_h2d.a_valid <= 1'b0;

  // Wait for read response d_valid
  while (!tl_d2h.d_valid) begin
    @(posedge clk);
  end

  data = tl_d2h.d_data;
  err  = tl_d2h.d_error;
endtask
  

  logic [31:0] rd;
  logic        rerr;

  initial begin
  $monitor("t=%0t rst_n=%0b a_valid=%0b a_ready=%0b d_valid=%0b req=%0b gnt=%0b we=%0b rvalid=%0b addr=%0d wdata=%08h CEN=%0b GWEN=%0b",
             $time, rst_n, tl_h2d.a_valid, tl_d2h.a_ready, tl_d2h.d_valid,
             dut.req, dut.gnt, dut.we, dut.rvalid, dut.addr, dut.wdata,
             dut.u_mem.gen_byte[0].u_macro.CEN, dut.u_mem.gen_byte[0].u_macro.GWEN);
  
 end

  initial begin
    $dumpfile("wave.fst");
    $dumpvars(0, tb_tlul_sram_if_macro);
	tl_h2d = TL_H2D_DEFAULT;
    repeat (3) @(posedge clk);
    rst_n = 1;
    repeat (2) @(posedge clk);

    // word 0 (byte address 0x0)
    tl_write(32'h0000_0000, 32'hDEADBEEF);
    tl_read (32'h0000_0000, rd, rerr);
    if (rerr || rd !== 32'hDEADBEEF) begin
      $display("FAIL: word0 expected DEADBEEF, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: word0 readback = %08h", rd);

    // last word in the 256-deep window (byte address 0x3FC = word 255)
    tl_write(32'h0000_03FC, 32'h12345678);
    tl_read (32'h0000_03FC, rd, rerr);
    if (rerr || rd !== 32'h12345678) begin
      $display("FAIL: word255 expected 12345678, got %08h (err=%0b)", rd, rerr);
      errors++;
    end else $display("PASS: word255 (top of 1KiB window) readback = %08h", rd);

    // re-read word 0 to confirm no cross-talk from the word255 write
    tl_read(32'h0000_0000, rd, rerr);
    if (rerr || rd !== 32'hDEADBEEF) begin
      $display("FAIL: word0 corrupted after word255 write, got %08h", rd);
      errors++;
    end else $display("PASS: word0 unaffected by word255 write = %08h", rd);

    if (errors == 0) $display("\n=== ALL REAL-PATH TESTS PASSED (tlul_sram_if_macro -> prim_ram_1p_macro -> gf180mcu_ocd_ip_sram__sram256x8m8wm1) ===");
    else              $display("\n=== %0d TEST(S) FAILED ===", errors);

    $finish;
  end

  initial begin
    #100000;
    $display("TIMEOUT: simulation did not complete in time (dut likely stuck waiting on a_ready/d_valid)");
    $finish;
  end

endmodule
