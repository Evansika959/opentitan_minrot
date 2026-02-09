// TL-UL ROM interface: adapter + simple 1-cycle ROM model (read-only)
module tlul_rom_if #(
	parameter int unsigned RomAw = 14,
	parameter string INIT_HEX = ""
) (
	input  logic              clk_i,
	input  logic              rst_ni,
	input  tlul_pkg::tl_h2d_t tl_i,
	output tlul_pkg::tl_d2h_t tl_o,
	input  prim_mubi_pkg::mubi4_t en_ifetch_i
);
	import tlul_pkg::*;

	logic req, we, gnt, rvalid;
	prim_mubi_pkg::mubi4_t req_type;
	logic [RomAw-1:0] addr;
	logic [31:0] wdata;
	logic [3:0]  wmask;
	logic [31:0] rdata;
	logic [1:0]  rerror;

	assign gnt    = 1'b1;
	assign rerror = 2'b00;

	tlul_adapter_sram #(
		.SramAw(RomAw),
		.SramDw(32),
		.Outstanding(1),
		.ByteAccess(1),
		.CmdIntgCheck(0),
		.EnableRspIntgGen(0),
		.EnableDataIntgGen(0),
		.EnableDataIntgPt(0)
	) u_adapt (
		.clk_i, .rst_ni,
		.tl_i, .tl_o,
		.en_ifetch_i(en_ifetch_i),

		.req_o(req),
		.req_type_o(req_type),
		.gnt_i(gnt),
		.we_o(we),
		.addr_o(addr),
		.wdata_o(wdata),
		.wmask_o(wmask),

		.intg_error_o(),

		.rdata_i(rdata),
		.rvalid_i(rvalid),
		.rerror_i(rerror)
	);

	// 1-cycle read ROM model. Writes are ignored (read-only).
	logic [31:0] mem [0:(1<<RomAw)-1];
	initial if (INIT_HEX != "") $readmemh(INIT_HEX, mem);

	logic [RomAw-1:0] rd_addr_q;
	logic rd_pending_q;

	always_ff @(posedge clk_i or negedge rst_ni) begin
		if (!rst_ni) begin
			rvalid       <= 1'b0;
			rdata        <= '0;
			rd_addr_q    <= '0;
			rd_pending_q <= 1'b0;
		end else begin
			rvalid <= 1'b0;

			// Ignore writes (ROM). Optionally could flag an error here.

			if (req && !we) begin
				rd_addr_q    <= addr;
				rd_pending_q <= 1'b1;
			end

			if (rd_pending_q) begin
				rdata        <= mem[rd_addr_q];
				rvalid       <= 1'b1;
				rd_pending_q <= 1'b0;
			end
		end
	end
endmodule
