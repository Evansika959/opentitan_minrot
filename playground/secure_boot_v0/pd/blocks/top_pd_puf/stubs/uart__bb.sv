// Auto-generated black-box stub (ports from netlist).
(* blackbox *)
module uart (cio_rx_i,
    cio_tx_en_o,
    cio_tx_o,
    clk_i,
    intr_rx_break_err_o,
    intr_rx_frame_err_o,
    intr_rx_overflow_o,
    intr_rx_parity_err_o,
    intr_rx_timeout_o,
    intr_rx_watermark_o,
    intr_tx_done_o,
    intr_tx_empty_o,
    intr_tx_watermark_o,
    lsio_trigger_o,
    rst_ni,
    alert_rx_i,
    alert_tx_o,
    racl_error_o,
    racl_policies_i,
    tl_i,
    tl_o);
   input cio_rx_i;
   output cio_tx_en_o;
   output cio_tx_o;
   input clk_i;
   output intr_rx_break_err_o;
   output intr_rx_frame_err_o;
   output intr_rx_overflow_o;
   output intr_rx_parity_err_o;
   output intr_rx_timeout_o;
   output intr_rx_watermark_o;
   output intr_tx_done_o;
   output intr_tx_empty_o;
   output intr_tx_watermark_o;
   output lsio_trigger_o;
   input rst_ni;
   input [3:0] alert_rx_i;
   output [1:0] alert_tx_o;
   output [43:0] racl_error_o;
   input [95:0] racl_policies_i;
   input [113:0] tl_i;
   output [65:0] tl_o;
endmodule
