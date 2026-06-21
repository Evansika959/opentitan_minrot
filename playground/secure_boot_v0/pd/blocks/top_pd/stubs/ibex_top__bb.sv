// Auto-generated black-box stub (ports from netlist).
(* blackbox *)
module ibex_top (alert_major_bus_o,
    alert_major_internal_o,
    alert_minor_o,
    clk_i,
    core_sleep_o,
    data_err_i,
    data_gnt_i,
    data_req_o,
    data_rvalid_i,
    data_we_o,
    debug_req_i,
    double_fault_seen_o,
    instr_err_i,
    instr_gnt_i,
    instr_req_o,
    instr_rvalid_i,
    irq_external_i,
    irq_nm_i,
    irq_software_i,
    irq_timer_i,
    rst_ni,
    scan_rst_ni,
    scramble_key_valid_i,
    scramble_req_o,
    test_en_i,
    boot_addr_i,
    crash_dump_o,
    data_addr_o,
    data_be_o,
    data_rdata_i,
    data_rdata_intg_i,
    data_wdata_intg_o,
    data_wdata_o,
    fetch_enable_i,
    hart_id_i,
    instr_addr_o,
    instr_rdata_i,
    instr_rdata_intg_i,
    irq_fast_i,
    ram_cfg_icache_data_i,
    ram_cfg_icache_tag_i,
    ram_cfg_rsp_icache_data_o,
    ram_cfg_rsp_icache_tag_o,
    scramble_key_i,
    scramble_nonce_i);
   output alert_major_bus_o;
   output alert_major_internal_o;
   output alert_minor_o;
   input clk_i;
   output core_sleep_o;
   input data_err_i;
   input data_gnt_i;
   output data_req_o;
   input data_rvalid_i;
   output data_we_o;
   input debug_req_i;
   output double_fault_seen_o;
   input instr_err_i;
   input instr_gnt_i;
   output instr_req_o;
   input instr_rvalid_i;
   input irq_external_i;
   input irq_nm_i;
   input irq_software_i;
   input irq_timer_i;
   input rst_ni;
   input scan_rst_ni;
   input scramble_key_valid_i;
   output scramble_req_o;
   input test_en_i;
   input [31:0] boot_addr_i;
   output [159:0] crash_dump_o;
   output [31:0] data_addr_o;
   output [3:0] data_be_o;
   input [31:0] data_rdata_i;
   input [6:0] data_rdata_intg_i;
   output [6:0] data_wdata_intg_o;
   output [31:0] data_wdata_o;
   input [3:0] fetch_enable_i;
   input [31:0] hart_id_i;
   output [31:0] instr_addr_o;
   input [31:0] instr_rdata_i;
   input [6:0] instr_rdata_intg_i;
   input [14:0] irq_fast_i;
   input [11:0] ram_cfg_icache_data_i;
   input [11:0] ram_cfg_icache_tag_i;
   output [1:0] ram_cfg_rsp_icache_data_o;
   output [1:0] ram_cfg_rsp_icache_tag_o;
   input [127:0] scramble_key_i;
   input [63:0] scramble_nonce_i;
endmodule
