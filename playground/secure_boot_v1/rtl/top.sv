
module top #(
  // Address width; IMEM/DMEM default to 64 KiB to match link.ld (0x10000 bytes)
  parameter int unsigned IMEM_AW = 16,
  parameter int unsigned DMEM_AW = 16,
  // Default program image for instruction memory
  parameter string IMEM_INIT_HEX = "/home/xinting/opentitan_minrot/playground/secure_boot_v1/test_sw/hex/otbn_demo.imem.hex",
  parameter string DMEM_INIT_HEX = "/home/xinting/opentitan_minrot/playground/secure_boot_v1/test_sw/hex/otbn_demo.dmem.hex",
  parameter int IMEM_BASE = 32'h0000_0000,
  parameter int UART_BASE = 32'h0003_0000
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
  import tl_tlul_main_pkg::*;
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

  tl_h2d_t tl_to_hmac;
  tl_d2h_t tl_from_hmac;

  tl_h2d_t tl_to_otbn;
  tl_d2h_t tl_from_otbn;

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
    // Ibex reset PC: skip the 0x00-0x7F padding we prepend in IMEM hex
    .boot_addr_i(IMEM_BASE + 32'h80),

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
    .INIT_HEX(),
    .BASE_ADDR(32'h0001_0000)
  ) u_esram (
    .clk_i(clk_i), .rst_ni(rst_ni),
    .tl_i(tl_to_esram), .tl_o(tl_from_esram),
    .en_ifetch_i(prim_mubi_pkg::MuBi4True)
  );

  // DMEM SRAM
  tlul_sram_if #(
    .SramAw(DMEM_AW),
    .INIT_HEX(DMEM_INIT_HEX),
    .BASE_ADDR(32'h0002_0000)
  ) u_dmem (
    .clk_i(clk_i), .rst_ni(rst_ni),
    .tl_i(tl_to_dmem_sram), .tl_o(tl_from_dmem_sram),
    .en_ifetch_i(prim_mubi_pkg::MuBi4False)
  );

  // xbar instantiation (main fabric with ROM/ESRAM/DMEM/UART/HMAC/OTBN)
  xbar_tlul_main u_xbar (
    .clk_i(clk_i),
    .rst_ni(rst_ni),

    // Hosts
    .tl_h_i_i(tl_imem_h2d),
    .tl_h_i_o(tl_imem_d2h),
    .tl_h_d_i(tl_dmem_h2d),
    .tl_h_d_o(tl_dmem_d2h),

    // Devices
    .tl_d_rom_o(tl_to_rom),
    .tl_d_rom_i(tl_from_rom),
    .tl_d_esram_o(tl_to_esram),
    .tl_d_esram_i(tl_from_esram),
    .tl_d_dmem_o(tl_to_dmem_sram),
    .tl_d_dmem_i(tl_from_dmem_sram),
    .tl_d_uart_o(tl_to_uart),
    .tl_d_uart_i(tl_from_uart),
    .tl_d_hmac_o(tl_to_hmac),
    .tl_d_hmac_i(tl_from_hmac),
    .tl_d_otbn_o(tl_to_otbn),
    .tl_d_otbn_i(tl_from_otbn),

    .scanmode_i(prim_mubi_pkg::MuBi4False)
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

  // HMAC device (interrupts/alerts are unused here)
  localparam int HMAC_NUM_ALERTS = hmac_reg_pkg::NumAlerts;
  prim_alert_pkg::alert_rx_t [HMAC_NUM_ALERTS-1:0] hmac_alert_rx;
  prim_alert_pkg::alert_tx_t [HMAC_NUM_ALERTS-1:0] hmac_alert_tx;
  initial hmac_alert_rx = '{default:'0};

  logic hmac_intr_done, hmac_intr_fifo_empty, hmac_intr_err;
  prim_mubi_pkg::mubi4_t hmac_idle;

  hmac u_hmac (
    .clk_i(clk_i),
    .rst_ni(rst_ni),
    .tl_i(tl_to_hmac),
    .tl_o(tl_from_hmac),
    .alert_rx_i(hmac_alert_rx),
    .alert_tx_o(hmac_alert_tx),
    .intr_hmac_done_o(hmac_intr_done),
    .intr_fifo_empty_o(hmac_intr_fifo_empty),
    .intr_hmac_err_o(hmac_intr_err),
    .idle_o(hmac_idle)
  );

  // OTBN device (basic configuration; interrupts/alerts tied off)
  localparam int OTBN_NUM_ALERTS = otbn_reg_pkg::NumAlerts;
  prim_alert_pkg::alert_rx_t [OTBN_NUM_ALERTS-1:0] otbn_alert_rx =
      '{default: prim_alert_pkg::ALERT_RX_DEFAULT};
  prim_alert_pkg::alert_tx_t [OTBN_NUM_ALERTS-1:0] otbn_alert_tx;

  prim_mubi_pkg::mubi4_t otbn_idle;
  logic otbn_intr_done;

  prim_ram_1p_pkg::ram_1p_cfg_t     otbn_ram_cfg_imem;
  prim_ram_1p_pkg::ram_1p_cfg_t     otbn_ram_cfg_dmem;
  prim_ram_1p_pkg::ram_1p_cfg_rsp_t otbn_ram_cfg_rsp_imem;
  prim_ram_1p_pkg::ram_1p_cfg_rsp_t otbn_ram_cfg_rsp_dmem;

  edn_pkg::edn_req_t otbn_edn_rnd_req;
  edn_pkg::edn_rsp_t otbn_edn_rnd_rsp;
  edn_pkg::edn_req_t otbn_edn_urnd_req;
  edn_pkg::edn_rsp_t otbn_edn_urnd_rsp;

  otp_ctrl_pkg::otbn_otp_key_req_t otbn_otp_key_req;
  otp_ctrl_pkg::otbn_otp_key_rsp_t otbn_otp_key_rsp;

  keymgr_pkg::otbn_key_req_t otbn_keymgr_key;

  // Tie off optional interfaces for a minimal build
  assign otbn_ram_cfg_imem = prim_ram_1p_pkg::RAM_1P_CFG_DEFAULT;
  assign otbn_ram_cfg_dmem = prim_ram_1p_pkg::RAM_1P_CFG_DEFAULT;
  // Provide simple, valid EDN responses to satisfy OTBN's repetition checks.
  logic [31:0] otbn_edn_rnd_data;
  logic [31:0] otbn_edn_urnd_data;

  function automatic logic [31:0] lfsr32_step(input logic [31:0] state);
    logic feedback;
    begin
      feedback = state[31] ^ state[21] ^ state[1] ^ state[0];
      lfsr32_step = {state[30:0], feedback};
    end
  endfunction

  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      otbn_edn_rnd_data  <= 32'h1;
      otbn_edn_urnd_data <= 32'h2;
    end else begin
      if (otbn_edn_rnd_req.edn_req) begin
        otbn_edn_rnd_data <= lfsr32_step(otbn_edn_rnd_data);
      end
      if (otbn_edn_urnd_req.edn_req) begin
        otbn_edn_urnd_data <= lfsr32_step(otbn_edn_urnd_data);
      end
    end
  end

  assign otbn_edn_rnd_rsp.edn_ack  = otbn_edn_rnd_req.edn_req;
  assign otbn_edn_rnd_rsp.edn_fips = 1'b1;
  assign otbn_edn_rnd_rsp.edn_bus  = otbn_edn_rnd_data;

  assign otbn_edn_urnd_rsp.edn_ack  = otbn_edn_urnd_req.edn_req;
  assign otbn_edn_urnd_rsp.edn_fips = 1'b1;
  assign otbn_edn_urnd_rsp.edn_bus  = otbn_edn_urnd_data;

  // Handshake OTP key response only when requested to avoid spurious acks.
  assign otbn_otp_key_rsp.ack        = otbn_otp_key_req.req;
  assign otbn_otp_key_rsp.key        = '0;
  assign otbn_otp_key_rsp.nonce      = '0;
  assign otbn_otp_key_rsp.seed_valid = 1'b1;

  assign otbn_keymgr_key = keymgr_pkg::OTBN_KEY_REQ_DEFAULT;

  otbn u_otbn (
    .clk_i(clk_i),
    .rst_ni(rst_ni),

    .tl_i(tl_to_otbn),
    .tl_o(tl_from_otbn),

    .idle_o(otbn_idle),
    .intr_done_o(otbn_intr_done),

    .alert_rx_i(otbn_alert_rx),
    .alert_tx_o(otbn_alert_tx),

    .lc_escalate_en_i(lc_ctrl_pkg::Off),
    .lc_rma_req_i(lc_ctrl_pkg::Off),
    .lc_rma_ack_o(),

    .ram_cfg_imem_i(otbn_ram_cfg_imem),
    .ram_cfg_dmem_i(otbn_ram_cfg_dmem),
    .ram_cfg_rsp_imem_o(otbn_ram_cfg_rsp_imem),
    .ram_cfg_rsp_dmem_o(otbn_ram_cfg_rsp_dmem),

    .clk_edn_i(clk_i),
    .rst_edn_ni(rst_ni),
    .edn_rnd_o(otbn_edn_rnd_req),
    .edn_rnd_i(otbn_edn_rnd_rsp),
    .edn_urnd_o(otbn_edn_urnd_req),
    .edn_urnd_i(otbn_edn_urnd_rsp),

    .clk_otp_i(clk_i),
    .rst_otp_ni(rst_ni),
    .otbn_otp_key_o(otbn_otp_key_req),
    .otbn_otp_key_i(otbn_otp_key_rsp),

    .keymgr_key_i(otbn_keymgr_key)
  );

  // Silence unused warnings
  logic unused_hmac;
  logic unused_otbn;
  assign unused_hmac = ^{hmac_intr_done, hmac_intr_fifo_empty, hmac_intr_err, hmac_idle};
  assign unused_otbn = ^{otbn_idle, otbn_intr_done, otbn_alert_tx, otbn_ram_cfg_rsp_imem,
                         otbn_ram_cfg_rsp_dmem, otbn_edn_rnd_req, otbn_edn_urnd_req,
                         otbn_otp_key_req};

  // Expose UART TL for TB visibility
  assign tl_to_uart_o   = tl_to_uart;
  assign tl_from_uart_o = tl_from_uart;

  // Expose exec SRAM dump to TB (called by top_tb)
  function automatic void dump_esram(input string path);
    begin
      u_esram.dump_mem(path);
    end
  endfunction

endmodule
