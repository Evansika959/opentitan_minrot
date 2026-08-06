`timescale 1ns/1ps
module dffrnq_iso_tb;
  logic clk, rn, d, q;
  initial clk = 0;
  always #30 clk = ~clk;

  gf180mcu_fd_sc_mcu7t5v0__dffrnq_1 dut (.CLK(clk), .D(d), .RN(rn), .Q(q));

  initial begin
    d  = 1'b1;   // D held high the whole time -- if reset works, Q must still be 0 while RN=0
    rn = 1'b0;   // assert reset immediately at time 0
    $display("[ISO] t=%0t rn=%b d=%b q=%b (expect q=0, reset asserted)", $time, rn, d, q);
    #100;
    $display("[ISO] t=%0t rn=%b d=%b q=%b (expect q=0, still in reset)", $time, rn, d, q);
    repeat (5) @(posedge clk);
    $display("[ISO] t=%0t rn=%b d=%b q=%b (expect q=0, still in reset, after clock edges)", $time, rn, d, q);
    rn = 1'b1;   // release reset
    @(posedge clk);
    $display("[ISO] t=%0t rn=%b d=%b q=%b (expect q=1 now: reset released, D=1 captured on edge)", $time, rn, d, q);
    $finish;
  end
endmodule
