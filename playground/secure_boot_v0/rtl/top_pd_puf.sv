// top_pd_puf.sv -- new file.
//
// Full-chip PD integration top reflecting tonight's simulated architecture
// (puf_secure_boot_macro21_top.sv), NOT the older top_pd.sv (4-port xbar,
// no PUF, all-1KiB-FD-macro memories). Hardened blocks are (* blackbox *)
// stubs (stubs/) so synthesis keeps them as hard macros, exactly like
// top_pd.sv's own convention -- physical views come from MACROS in
// config.json, not from RTL flattening.
//
// Memory plan (matches what was actually simulated and confirmed PASS):
//   IMEM  = tlul_sram_if_macro_ocd_21bank (real, already hardened -- 21
//           banks/84 real gf180mcu_ocd_ip_sram256x8 macro instances,
//           exported via export_macros.sh, zero new PD work).
//   ESRAM = tlul_sram_if_macro (real, already hardened -- the original
//           1 KiB FD-family macro top_pd.sv already used for all three
//           memory roles; reused here unchanged).
//   DMEM  = tlul_sram_if_macro (same, second instance).
// (ESRAM/DMEM stay on the smaller FD-family macro rather than switching to
// the OCD family, since that macro is already hardened and this is a
// "start slow" incremental step -- an OCD-family ESRAM would need its own
// new 1-bank hardening run, same as xbar_tlul_2to5 below.)
//
// PUF path (matches puf_secure_boot_macro21_top.sv's wiring exactly):
// tlul_adapter_reg + sram_puf_regif + sram_puf, kept as synthesizable glue
// (like ibex_to_tlul_host already is) rather than its own hardened macro --
// small enough to fold into this top's own synthesis. sram_puf.v's own
// entropy source is a real, already-signed-off GF180MCU foundry SRAM
// primitive (gf180mcu_fd_ip_sram__sram64x8m8wm1, blackboxed via the
// existing pd/pdk/.../__blackbox.v) -- NOT the analog xschem ring-
// oscillator PUF, which was never wired into this RTL and has no digital
// PD path (out of scope here).
//
// NEW hardening needed (the only piece without an existing physical view):
// xbar_tlul_2to5 -- the 5-port crossbar (adds the PUF device port onto the
// existing xbar_tlul_2to4 pattern). Everything else below is either
// already-hardened (exported to pd/macros/) or small synthesizable glue.
module top_pd_puf (
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
  tl_h2d_t tl_to_puf;        tl_d2h_t tl_from_puf;

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
    .hart_id_i(32'h0), .boot_addr_i(IMEM_BASE),
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
  // IMEM: real 21-bank OCD block -- READ_ONLY/NumBanks are baked into the
  // netlist already hardened under pd/blocks/tlul_sram_if_macro_ocd_21bank.
  tlul_sram_if_macro_ocd_21bank u_imem (.clk_i, .rst_ni, .tl_i(tl_to_rom),       .tl_o(tl_from_rom),       .en_ifetch_i(prim_mubi_pkg::MuBi4True));
  tlul_sram_if_macro           u_esram (.clk_i, .rst_ni, .tl_i(tl_to_esram),     .tl_o(tl_from_esram),     .en_ifetch_i(prim_mubi_pkg::MuBi4True));
  tlul_sram_if_macro           u_dmem  (.clk_i, .rst_ni, .tl_i(tl_to_dmem_sram), .tl_o(tl_from_dmem_sram), .en_ifetch_i(prim_mubi_pkg::MuBi4False));

  // ================= PUF (glue logic + real foundry SRAM primitive) =================
  logic        puf_re, puf_we;
  logic [7:0]  puf_addr;
  logic [31:0] puf_wdata, puf_rdata;
  logic [3:0]  puf_be;
  logic        puf_intg_err;

  tlul_adapter_reg #(
    .RegAw(8),
    .RegDw(32)
  ) u_puf_tl_adapter (
    .clk_i(clk_i), .rst_ni(rst_ni),
    .tl_i(tl_to_puf), .tl_o(tl_from_puf),
    .en_ifetch_i(prim_mubi_pkg::MuBi4False),
    .intg_error_o(puf_intg_err),
    .re_o(puf_re), .we_o(puf_we), .addr_o(puf_addr),
    .wdata_o(puf_wdata), .be_o(puf_be),
    .busy_i(1'b0),
    .rdata_i(puf_rdata), .error_i(1'b0)
  );

  sram_puf_regif u_puf_regif (
    .clk_i  (clk_i),
    .rst_ni (rst_ni),
    .req_i  (puf_re || puf_we),
    .we_i   (puf_we),
    .addr_i ({24'b0, puf_addr}),
    .wdata_i(puf_wdata),
    .rdata_o(puf_rdata)
  );

  // ================= Crossbar (hard macro -- NEW, needs hardening) =================
  xbar_tlul_2to5 u_xbar (
    .clk_i(clk_i),
    .rst_ni(rst_ni),
    .tl_h_i_i(tl_imem_h2d),
    .tl_h_i_o(tl_imem_d2h),
    .tl_h_d_i(tl_dmem_h2d),
    .tl_h_d_o(tl_dmem_d2h),
    .tl_d_rom_o(tl_to_rom),         .tl_d_rom_i(tl_from_rom),
    .tl_d_esram_o(tl_to_esram),     .tl_d_esram_i(tl_from_esram),
    .tl_d_dmem_o(tl_to_dmem_sram),  .tl_d_dmem_i(tl_from_dmem_sram),
    .tl_d_uart_o(tl_to_uart),       .tl_d_uart_i(tl_from_uart),
    .tl_d_puf_o(tl_to_puf),         .tl_d_puf_i(tl_from_puf),
    .scanmode_i(prim_mubi_pkg::MuBi4False)
  );

  // ================= UART (hard macro) =================
  prim_alert_pkg::alert_rx_t [0:0] uart_alert_rx;
  prim_alert_pkg::alert_tx_t [0:0] uart_alert_tx;
  assign uart_alert_rx = '{default:'0};
  uart u_uart (
    .clk_i, .rst_ni, .tl_i(tl_to_uart), .tl_o(tl_from_uart),
    .racl_policies_i('0), .racl_error_o(),
    .alert_rx_i(uart_alert_rx), .alert_tx_o(uart_alert_tx),
    .cio_rx_i(uart_rx_i), .cio_tx_o(uart_tx_o), .cio_tx_en_o(uart_tx_en_o),
    .intr_tx_watermark_o(), .intr_rx_watermark_o(), .intr_tx_empty_o(), .intr_rx_overflow_o(),
    .intr_rx_frame_err_o(), .intr_rx_break_err_o(), .intr_rx_timeout_o(), .intr_rx_parity_err_o()
  );

endmodule
