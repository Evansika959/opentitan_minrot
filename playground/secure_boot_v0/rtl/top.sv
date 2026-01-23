
module top #(
  parameter int unsigned IMEM_AW = 16,
  parameter int unsigned DMEM_AW = 16,
  parameter string IMEM_INIT_HEX = "/home/xinting/opentitan_minrot/playground/pure_ibex_uart/imem.hex",
  parameter string DMEM_INIT_HEX = "/home/xinting/opentitan_minrot/playground/pure_ibex_uart/dmem.hex",
  parameter int IMEM_BASE = 32'h0000_0000
) (
  input  logic clk_i,
  input  logic rst_ni,

  // expose UART TL-UL device port (for TB monitoring)
  output tlul_pkg::tl_h2d_t tl_to_uart_o,
  output tlul_pkg::tl_d2h_t tl_from_uart_o,

  input  logic uart_rx_i,
  output logic uart_tx_o,
  output logic uart_tx_en_o

`ifdef RVFI
  ,output logic        rvfi_valid
  ,output logic [63:0] rvfi_order
  ,output logic [31:0] rvfi_insn
  ,output logic        rvfi_trap
  ,output logic        rvfi_halt
  ,output logic        rvfi_intr
  ,output logic [1:0]  rvfi_mode
  ,output logic [1:0]  rvfi_ixl
  ,output logic [4:0]  rvfi_rs1_addr
  ,output logic [4:0]  rvfi_rs2_addr
  ,output logic [4:0]  rvfi_rs3_addr
  ,output logic [31:0] rvfi_rs1_rdata
  ,output logic [31:0] rvfi_rs2_rdata
  ,output logic [31:0] rvfi_rs3_rdata
  ,output logic [4:0]  rvfi_rd_addr
  ,output logic [31:0] rvfi_rd_wdata
  ,output logic [31:0] rvfi_pc_rdata
  ,output logic [31:0] rvfi_pc_wdata
  ,output logic [31:0] rvfi_mem_addr
  ,output logic [3:0]  rvfi_mem_rmask
  ,output logic [3:0]  rvfi_mem_wmask
  ,output logic [31:0] rvfi_mem_rdata
  ,output logic [31:0] rvfi_mem_wdata
  ,output logic [31:0] rvfi_ext_pre_mip
  ,output logic [31:0] rvfi_ext_post_mip
  ,output logic        rvfi_ext_nmi
  ,output logic        rvfi_ext_nmi_int
  ,output logic        rvfi_ext_debug_req
  ,output logic        rvfi_ext_debug_mode
  ,output logic        rvfi_ext_rf_wr_suppress
  ,output logic [63:0] rvfi_ext_mcycle
  ,output logic [31:0] rvfi_ext_mhpmcounters [10]
  ,output logic [31:0] rvfi_ext_mhpmcountersh [10]
  ,output logic        rvfi_ext_ic_scr_key_valid
  ,output logic        rvfi_ext_irq_valid
`endif
);
  import top_pkg::*;
  import tlul_pkg::*;
  import ibex_pkg::*;

  // TL wires
  tl_h2d_t tl_imem_h2d;
  tl_d2h_t tl_imem_d2h;

  tl_h2d_t tl_dmem_h2d;
  tl_d2h_t tl_dmem_d2h;

  tl_h2d_t tl_to_rom;
  tl_d2h_t tl_from_rom;

  tl_h2d_t tl_to_esram;
  tl_d2h_t tl_from_esram;

  tl_h2d_t tl_to_dmem_sram;
  tl_d2h_t tl_from_dmem_sram;

  tl_h2d_t tl_to_uart;
  tl_d2h_t tl_from_uart;

  // Ibex instruction/data handshake wires
  logic instr_req, instr_gnt, instr_rvalid;
  logic [31:0] instr_addr, instr_rdata;
  logic instr_err;

  logic data_req, data_gnt, data_rvalid;
  logic data_we;
  logic [3:0]  data_be;
  logic [31:0] data_addr, data_wdata, data_rdata;
  logic data_err;

  // Alert/ctrl wires (tied off for now)
  logic alert_minor, alert_major_int, alert_major_bus;
  logic core_sleep;

  // Ibex core (upstream ibex_top)
  ibex_top u_ibex (
    .clk_i(clk_i),
    .rst_ni(rst_ni),
    .test_en_i(1'b0),
    .ram_cfg_icache_tag_i(prim_ram_1p_pkg::RAM_1P_CFG_DEFAULT),
    .ram_cfg_rsp_icache_tag_o(),
    .ram_cfg_icache_data_i(prim_ram_1p_pkg::RAM_1P_CFG_DEFAULT),
    .ram_cfg_rsp_icache_data_o(),
    .hart_id_i(32'h0),
    .boot_addr_i(IMEM_BASE),

    // Instruction interface
    .instr_req_o(instr_req),
    .instr_gnt_i(instr_gnt),
    .instr_rvalid_i(instr_rvalid),
    .instr_addr_o(instr_addr),
    .instr_rdata_i(instr_rdata),
    .instr_rdata_intg_i('0),
    .instr_err_i(instr_err),

    // Data interface
    .data_req_o(data_req),
    .data_gnt_i(data_gnt),
    .data_rvalid_i(data_rvalid),
    .data_we_o(data_we),
    .data_be_o(data_be),
    .data_addr_o(data_addr),
    .data_wdata_o(data_wdata),
    .data_wdata_intg_o(),
    .data_rdata_i(data_rdata),
    .data_rdata_intg_i('0),
    .data_err_i(data_err),

    // Interrupts disabled
    .irq_software_i (1'b0),
    .irq_timer_i    (1'b0),
    .irq_external_i (1'b0),
    .irq_fast_i     ('0),
    .irq_nm_i       (1'b0),

    // CPU control / alerts
    .fetch_enable_i(ibex_pkg::IbexMuBiOn),
    .alert_minor_o(alert_minor),
    .alert_major_internal_o(alert_major_int),
    .alert_major_bus_o(alert_major_bus),
    .core_sleep_o(core_sleep),

    // DFT bypass
    .scan_rst_ni(1'b1),

    // Scrambling/Debug unused
    .scramble_key_valid_i(1'b0),
    .scramble_key_i('0),
    .scramble_nonce_i('0),
    .scramble_req_o(),
    .debug_req_i(1'b0),
    .crash_dump_o(),
    .double_fault_seen_o()

`ifdef RVFI
    , .rvfi_valid(rvfi_valid), .rvfi_order(rvfi_order), .rvfi_insn(rvfi_insn),
      .rvfi_trap(rvfi_trap), .rvfi_halt(rvfi_halt), .rvfi_intr(rvfi_intr),
      .rvfi_mode(rvfi_mode), .rvfi_ixl(rvfi_ixl), .rvfi_rs1_addr(rvfi_rs1_addr),
      .rvfi_rs2_addr(rvfi_rs2_addr), .rvfi_rs3_addr(rvfi_rs3_addr),
      .rvfi_rs1_rdata(rvfi_rs1_rdata), .rvfi_rs2_rdata(rvfi_rs2_rdata),
      .rvfi_rs3_rdata(rvfi_rs3_rdata), .rvfi_rd_addr(rvfi_rd_addr),
      .rvfi_rd_wdata(rvfi_rd_wdata), .rvfi_pc_rdata(rvfi_pc_rdata),
      .rvfi_pc_wdata(rvfi_pc_wdata), .rvfi_mem_addr(rvfi_mem_addr),
      .rvfi_mem_rmask(rvfi_mem_rmask), .rvfi_mem_wmask(rvfi_mem_wmask),
      .rvfi_mem_rdata(rvfi_mem_rdata), .rvfi_mem_wdata(rvfi_mem_wdata),
      .rvfi_ext_pre_mip(rvfi_ext_pre_mip), .rvfi_ext_post_mip(rvfi_ext_post_mip),
      .rvfi_ext_nmi(rvfi_ext_nmi), .rvfi_ext_nmi_int(rvfi_ext_nmi_int),
      .rvfi_ext_debug_req(rvfi_ext_debug_req),
      .rvfi_ext_debug_mode(rvfi_ext_debug_mode),
      .rvfi_ext_rf_wr_suppress(rvfi_ext_rf_wr_suppress),
      .rvfi_ext_mcycle(rvfi_ext_mcycle),
      .rvfi_ext_mhpmcounters(rvfi_ext_mhpmcounters),
      .rvfi_ext_mhpmcountersh(rvfi_ext_mhpmcountersh),
      .rvfi_ext_ic_scr_key_valid(rvfi_ext_ic_scr_key_valid),
      .rvfi_ext_irq_valid(rvfi_ext_irq_valid)
`endif
  );

  // Adapters: Ibex mem -> TL-UL
  ibex_to_tlul_host #(.READ_ONLY(1)) u_instr2tl (
    .clk_i, .rst_ni,
    .req_i(instr_req), .we_i(1'b0), .be_i(4'hF), .addr_i(instr_addr), .wdata_i('0),
    .gnt_o(instr_gnt), .rvalid_o(instr_rvalid), .rdata_o(instr_rdata), .err_o(instr_err),
    .tl_o(tl_imem_h2d), .tl_i(tl_imem_d2h)
  );

  ibex_to_tlul_host #(.READ_ONLY(0)) u_data2tl (
    .clk_i, .rst_ni,
    .req_i(data_req), .we_i(data_we), .be_i(data_be), .addr_i(data_addr), .wdata_i(data_wdata),
    .gnt_o(data_gnt), .rvalid_o(data_rvalid), .rdata_o(data_rdata), .err_o(data_err),
    .tl_o(tl_dmem_h2d), .tl_i(tl_dmem_d2h)
  );

  // IMEM ROM (Read only as in ROM)
  tlul_rom_if #(
    .RomAw(IMEM_AW),
    .INIT_HEX(IMEM_INIT_HEX)
  ) u_imem (
    .clk_i(clk_i), .rst_ni(rst_ni),
    .tl_i(tl_to_rom), .tl_o(tl_from_rom),
    .en_ifetch_i(prim_mubi_pkg::MuBi4True)
  );

  // IMEM SRAM (Exec SRAM) 
  tlul_sram_if #(
    .SramAw(IMEM_AW),
    .INIT_HEX("")
  ) u_esram (
    .clk_i(clk_i), .rst_ni(rst_ni),
    .tl_i(tl_to_esram), .tl_o(tl_from_esram),
    .en_ifetch_i(prim_mubi_pkg::MuBi4True)
  );

  // DMEM SRAM
  tlul_sram_if #(
    .SramAw(DMEM_AW),
    .INIT_HEX(DMEM_INIT_HEX)
  ) u_dmem (
    .clk_i(clk_i), .rst_ni(rst_ni),
    .tl_i(tl_to_dmem_sram), .tl_o(tl_from_dmem_sram),
    .en_ifetch_i(prim_mubi_pkg::MuBi4False)
  );

  // xbar instantiation
  tlul_xbar_2x4 u_xbar (
    .clk_i(clk_i),
    .rst_ni(rst_ni),

    // Hosts
    .h_d_i(tl_dmem_h2d),
    .h_d_o(tl_dmem_d2h),
    .h_i_i(tl_imem_h2d),
    .h_i_o(tl_imem_d2h),

    // Devices
    .dev0_o(tl_to_rom),
    .dev0_i(tl_from_rom),

    .dev1_o(tl_to_dmem_sram),
    .dev1_i(tl_from_dmem_sram),

    .dev2_o(tl_to_esram),
    .dev2_i(tl_from_esram),

    .dev3_o(tl_to_uart),
    .dev3_i(tl_from_uart)
  );



  // UART device
  localparam int UART_NUM_ALERTS = 1;
  prim_alert_pkg::alert_rx_t [UART_NUM_ALERTS-1:0] uart_alert_rx;
  prim_alert_pkg::alert_tx_t [UART_NUM_ALERTS-1:0] uart_alert_tx;
  initial uart_alert_rx = '{default:'0};

  uart u_uart (
    .clk_i(clk_i),
    .rst_ni(rst_ni),
    .tl_i(tl_to_uart),
    .tl_o(tl_from_uart),
    .alert_rx_i(uart_alert_rx),
    .alert_tx_o(uart_alert_tx),
    .cio_rx_i(uart_rx_i),
    .cio_tx_o(uart_tx_o),
    .cio_tx_en_o(uart_tx_en_o),
    .intr_tx_watermark_o(),
    .intr_rx_watermark_o(),
    .intr_tx_empty_o(),
    .intr_rx_overflow_o(),
    .intr_rx_frame_err_o(),
    .intr_rx_break_err_o(),
    .intr_rx_timeout_o(),
    .intr_rx_parity_err_o()
  );

  // Expose UART TL for TB visibility
  assign tl_to_uart_o   = tl_to_uart;
  assign tl_from_uart_o = tl_from_uart;

endmodule
