
// MODIFIED for test: retargeted from gf180mcu_fd_ip_sram__sram256x8m8wm1 to

// gf180mcu_ocd_ip_sram__sram256x8m8wm1 (Tim Edwards / Open Circuit Design).

// Everything else is unchanged from your original prim_ram_1p_macro.sv --

// same port list, same polarities, same byte-lane structure -- since the

// two macros' LEF pin lists are identical.

module prim_ram_1p_macro_OCD import prim_ram_1p_pkg::*; #(

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

`ifndef SYNTHESIS

  initial begin

    if (Width != 32 || Depth != 256)

      $error("prim_ram_1p_macro: only Width=32, Depth=256 (1 KiB) is supported");

  end

`endif

  assign cfg_rsp_o = '0;

  logic unused;

  assign unused = ^{rst_ni, cfg_i};

  logic cen, gwen;

  assign cen  = ~req_i;

  assign gwen = ~(req_i & write_i);

  for (genvar b = 0; b < 4; b++) begin : gen_byte

    gf180mcu_ocd_ip_sram__sram256x8m8wm1 u_macro (

      .CLK  (clk_i),

      .CEN  (cen),

      .GWEN (gwen),

      .WEN  (~wmask_i[8*b +: 8]),

      .A    (addr_i),

      .D    (wdata_i[8*b +: 8]),

      .Q    (rdata_o[8*b +: 8])

    );

  end

endmodule

