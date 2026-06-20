// PD-aligned, macro-backed replacement for prim_ram_1p (gf180mcuD).
//
// Instantiates 4x gf180mcu_fd_ip_sram__sram256x8m8wm1 as byte lanes to build a
// 256-deep x 32-bit single-port SRAM (1 KiB). It is a drop-in for OpenTitan's
// prim_ram_1p: identical port signature and 1-cycle synchronous read, so the
// SAME netlist that LibreLane synthesises contains the real macro instances --
// which is exactly what LVS needs to match against the placed GDS.
//
// The behavioural prim_ram_1p (a reg array) is left untouched and remains the
// simulation model; this file is selected only for the physical-design/LVS flow.
module prim_ram_1p_macro import prim_ram_1p_pkg::*; #(
  parameter  int Width           = 32,
  parameter  int Depth           = 256,
  parameter  int DataBitsPerMask = 8,   // byte-granular write
  parameter      MemInitFile     = "",  // not supported by a hard macro; ignored
  localparam int Aw              = $clog2(Depth)
) (
  input  logic             clk_i,
  input  logic             rst_ni,
  input  logic             req_i,
  input  logic             write_i,
  input  logic [Aw-1:0]    addr_i,
  input  logic [Width-1:0] wdata_i,
  input  logic [Width-1:0] wmask_i,
  output logic [Width-1:0] rdata_o,   // valid one cycle after req_i
  input  ram_1p_cfg_t      cfg_i,
  output ram_1p_cfg_rsp_t  cfg_rsp_o
);

  // This wrapper is fixed to the gf180 sram256x8 tiling: 256 words x 32 bit.
`ifndef SYNTHESIS
  initial begin
    if (Width != 32 || Depth != 256)
      $error("prim_ram_1p_macro: only Width=32, Depth=256 (1 KiB) is supported");
  end
`endif

  // No macro self-test / margining hookup; tie the config response off.
  assign cfg_rsp_o = '0;
  logic unused;
  assign unused = ^{rst_ni, cfg_i};

  // Active-low controls shared by all four byte lanes.
  logic cen, gwen;
  assign cen  = ~req_i;                 // chip enable      (active low)
  assign gwen = ~(req_i & write_i);     // global write en  (active low)

  // Byte lane b owns data bits [8b+7 : 8b]. The macro's per-bit WEN (active low)
  // takes the (inverted) bit write-mask directly, preserving bit granularity.
  for (genvar b = 0; b < 4; b++) begin : gen_byte
    gf180mcu_fd_ip_sram__sram256x8m8wm1 u_macro (
      .CLK  (clk_i),
      .CEN  (cen),
      .GWEN (gwen),
      .WEN  (~wmask_i[8*b +: 8]),
      .A    (addr_i),
      .D    (wdata_i[8*b +: 8]),
      .Q    (rdata_o[8*b +: 8]),
      .VDD  (),   // connected to the PDN in PnR (PDN_MACRO_CONNECTIONS)
      .VSS  ()
    );
  end

endmodule
