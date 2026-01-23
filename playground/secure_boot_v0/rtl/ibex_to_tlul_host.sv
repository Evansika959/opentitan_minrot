// Adapter: Ibex simple req/gnt interface to TL-UL host port (single outstanding)
module ibex_to_tlul_host #(
  parameter bit READ_ONLY = 1'b0
) (
  input  logic              clk_i,
  input  logic              rst_ni,

  // Ibex side
  input  logic              req_i,
  input  logic              we_i,
  input  logic [3:0]        be_i,
  input  logic [31:0]       addr_i,
  input  logic [31:0]       wdata_i,
  output logic              gnt_o,
  output logic              rvalid_o,
  output logic [31:0]       rdata_o,
  output logic              err_o,

  // TL-UL host port
  output tlul_pkg::tl_h2d_t tl_o,
  input  tlul_pkg::tl_d2h_t tl_i
);
  import tlul_pkg::*;
  import prim_mubi_pkg::*;

  logic outstanding_q;

  // defaults
  tlul_pkg::tl_h2d_t tl_d;
  always_comb begin
    tl_d = tlul_pkg::TL_H2D_DEFAULT;
    tl_d.a_valid   = req_i && !outstanding_q;
    tl_d.a_opcode  = (READ_ONLY || !we_i) ? tlul_pkg::Get : tlul_pkg::PutFullData;
    tl_d.a_param   = 3'b000;
    tl_d.a_size    = 3'd2; // 4 bytes
    tl_d.a_source  = '0;
    tl_d.a_address = addr_i;
    tl_d.a_mask    = (READ_ONLY || !we_i) ? 4'hF : be_i;
    tl_d.a_data    = wdata_i;
    tl_d.a_mask    = (READ_ONLY || !we_i) ? 4'hF : be_i;

    // Tag as data access and generate TL-UL integrity (ECC) bits
    tl_d.a_user.instr_type = MuBi4False;
    tl_d.a_user.cmd_intg   = tlul_pkg::get_cmd_intg(tl_d);
    tl_d.a_user.data_intg  = tlul_pkg::get_data_intg(tl_d.a_data);
  end
  assign tl_o = tl_d;

  // Ibex handshake
  assign gnt_o = tl_d.a_valid && tl_i.a_ready;

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      outstanding_q <= 1'b0;
      rvalid_o      <= 1'b0;
      rdata_o       <= '0;
      err_o         <= 1'b0;
    end else begin
      rvalid_o <= 1'b0;

      // launch request
      if (!outstanding_q && tl_d.a_valid && tl_i.a_ready) begin
        outstanding_q <= 1'b1;
      end

      // capture response
      if (outstanding_q && tl_i.d_valid) begin
        rdata_o       <= tl_i.d_data;
        err_o         <= tl_i.d_error;
        rvalid_o      <= 1'b1;
        outstanding_q <= 1'b0;
      end
    end
  end
endmodule
