// PD / full-chip integration top: the six hardened blocks instantiated as HARD
// MACROS (ibex_top, xbar_tlul_2to4, uart, tlul_sram_if_macro x3) plus the small
// glue that stays as std-cell logic (the two Ibex->TL-UL host adapters).
//
// NOT a simulation model: the blocks are (* blackbox *) here and the memories are
// 1 KiB hard macros (no $readmemh, no behaviour). Simulation keeps using
// rtl/top.sv (behavioural, 256 KiB). The three memory instances are the SAME
// hardened tlul_sram_if_macro (READ_ONLY / BASE_ADDR are baked to their defaults
// in the netlist); the ROM/IMEM/DMEM distinction is a floorplan label here.
module top_pd (
  input  logic clk_i,
  input  logic rst_ni,
  input  logic uart_rx_i,
  output logic uart_tx_o,
  output logic uart_tx_en_o
);
  import top_pkg::*;
  import tlul_pkg::*;
  import ibex_pkg::*;

  localparam int IMEM_BASE = 32'h0000_0000;

  // ---- TL-UL fabric nets ----
  tl_h2d_t tl_imem_h2d;      tl_d2h_t tl_imem_d2h;
  tl_h2d_t tl_dmem_h2d;      tl_d2h_t tl_dmem_d2h;
  tl_h2d_t tl_to_rom;        tl_d2h_t tl_from_rom;
  tl_h2d_t tl_to_esram;      tl_d2h_t tl_from_esram;
  tl_h2d_t tl_to_dmem_sram;  tl_d2h_t tl_from_dmem_sram;
  tl_h2d_t tl_to_uart;       tl_d2h_t tl_from_uart;

  // ---- Ibex instr/data handshake ----
  logic instr_req, instr_gnt, instr_rvalid;
  logic [31:0] instr_addr, instr_rdata;
  logic instr_err;
  logic data_req, data_gnt, data_rvalid, data_we;
  logic [3:0]  data_be;
  logic [31:0] data_addr, data_wdata, data_rdata;
  logic data_err;
  logic alert_minor, alert_major_int, alert_major_bus, core_sleep;

  // ================= Ibex core (hard macro) =================
  ibex_top u_ibex (
    .clk_i, .rst_ni, .test_en_i(1'b0),
    .ram_cfg_icache_tag_i (prim_ram_1p_pkg::RAM_1P_CFG_DEFAULT), .ram_cfg_rsp_icache_tag_o(),
    .ram_cfg_icache_data_i(prim_ram_1p_pkg::RAM_1P_CFG_DEFAULT), .ram_cfg_rsp_icache_data_o(),
    .hart_id_i(32'h0), .boot_addr_i(IMEM_BASE + 32'h80),
    .instr_req_o(instr_req), .instr_gnt_i(instr_gnt), .instr_rvalid_i(instr_rvalid),
    .instr_addr_o(instr_addr), .instr_rdata_i(instr_rdata), .instr_rdata_intg_i('0), .instr_err_i(instr_err),
    .data_req_o(data_req), .data_gnt_i(data_gnt), .data_rvalid_i(data_rvalid),
    .data_we_o(data_we), .data_be_o(data_be), .data_addr_o(data_addr), .data_wdata_o(data_wdata),
    .data_wdata_intg_o(), .data_rdata_i(data_rdata), .data_rdata_intg_i('0), .data_err_i(data_err),
    .irq_software_i(1'b0), .irq_timer_i(1'b0), .irq_external_i(1'b0), .irq_fast_i('0), .irq_nm_i(1'b0),
    .fetch_enable_i(ibex_pkg::IbexMuBiOn),
    .alert_minor_o(alert_minor), .alert_major_internal_o(alert_major_int),
    .alert_major_bus_o(alert_major_bus), .core_sleep_o(core_sleep), .scan_rst_ni(1'b1),
    .scramble_key_valid_i(1'b0), .scramble_key_i('0), .scramble_nonce_i('0), .scramble_req_o(),
    .debug_req_i(1'b0), .crash_dump_o(), .double_fault_seen_o()
  );

  // ================= Ibex mem -> TL-UL adapters (glue) =================
  ibex_to_tlul_host #(.READ_ONLY(1)) u_instr2tl (
    .clk_i, .rst_ni, .req_i(instr_req), .we_i(1'b0), .be_i(4'hF), .addr_i(instr_addr), .wdata_i('0),
    .gnt_o(instr_gnt), .rvalid_o(instr_rvalid), .rdata_o(instr_rdata), .err_o(instr_err),
    .tl_o(tl_imem_h2d), .tl_i(tl_imem_d2h)
  );
  ibex_to_tlul_host #(.READ_ONLY(0)) u_data2tl (
    .clk_i, .rst_ni, .req_i(data_req), .we_i(data_we), .be_i(data_be), .addr_i(data_addr), .wdata_i(data_wdata),
    .gnt_o(data_gnt), .rvalid_o(data_rvalid), .rdata_o(data_rdata), .err_o(data_err),
    .tl_o(tl_dmem_h2d), .tl_i(tl_dmem_d2h)
  );

  // ================= Memories (hard macros) =================
  tlul_sram_if_macro u_imem  (.clk_i, .rst_ni, .tl_i(tl_to_rom),       .tl_o(tl_from_rom),       .en_ifetch_i(prim_mubi_pkg::MuBi4True));   // ROM
  tlul_sram_if_macro u_esram (.clk_i, .rst_ni, .tl_i(tl_to_esram),     .tl_o(tl_from_esram),     .en_ifetch_i(prim_mubi_pkg::MuBi4True));   // IMEM
  tlul_sram_if_macro u_dmem  (.clk_i, .rst_ni, .tl_i(tl_to_dmem_sram), .tl_o(tl_from_dmem_sram), .en_ifetch_i(prim_mubi_pkg::MuBi4False));  // DMEM

  // ================= Crossbar (hard macro) =================
  xbar_tlul_2to4 u_xbar (
    .clk_i, .rst_ni,
    .tl_h_i_i(tl_imem_h2d), .tl_h_i_o(tl_imem_d2h),
    .tl_h_d_i(tl_dmem_h2d), .tl_h_d_o(tl_dmem_d2h),
    .tl_d_rom_o(tl_to_rom),         .tl_d_rom_i(tl_from_rom),
    .tl_d_esram_o(tl_to_esram),     .tl_d_esram_i(tl_from_esram),
    .tl_d_dmem_o(tl_to_dmem_sram),  .tl_d_dmem_i(tl_from_dmem_sram),
    .tl_d_uart_o(tl_to_uart),       .tl_d_uart_i(tl_from_uart),
    .scanmode_i(prim_mubi_pkg::MuBi4False)
  );

  // ================= UART (hard macro) =================
  prim_alert_pkg::alert_rx_t [0:0] uart_alert_rx;
  prim_alert_pkg::alert_tx_t [0:0] uart_alert_tx;
  assign uart_alert_rx = '{default:'0};
  uart u_uart (
    .clk_i, .rst_ni, .tl_i(tl_to_uart), .tl_o(tl_from_uart),
    .racl_policies_i('0), .racl_error_o(),   // darjeeling tlul RACL: no policy enforced
    .alert_rx_i(uart_alert_rx), .alert_tx_o(uart_alert_tx),
    .cio_rx_i(uart_rx_i), .cio_tx_o(uart_tx_o), .cio_tx_en_o(uart_tx_en_o),
    .intr_tx_watermark_o(), .intr_rx_watermark_o(), .intr_tx_empty_o(), .intr_rx_overflow_o(),
    .intr_rx_frame_err_o(), .intr_rx_break_err_o(), .intr_rx_timeout_o(), .intr_rx_parity_err_o()
  );

endmodule
