// Black-box declaration of the gf180 SRAM macro for synthesis + lint.
//
// The (* blackbox *) attribute tells Yosys to KEEP the instance (do not
// optimise it away even though the body is empty); slang/Verilator resolve
// the module reference and ignore the attribute. All physical/timing views
// (LEF / GDS / LIB / SPICE) are supplied separately via the MACROS config.
(* blackbox *)
module gf180mcu_fd_ip_sram__sram256x8m8wm1 (
  input  wire       CLK,
  input  wire       CEN,    // chip enable      (active low)
  input  wire       GWEN,   // global write en  (active low)
  input  wire [7:0] WEN,    // per-bit write en (active low)
  input  wire [7:0] A,
  input  wire [7:0] D,
  output wire [7:0] Q,
  inout  wire       VDD,
  inout  wire       VSS
);
endmodule
