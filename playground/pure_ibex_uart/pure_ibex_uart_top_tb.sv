// tb_pure_ibex_uart_top.sv
`define RVFI

module tb_pure_ibex_uart_top(
  input  logic clk,
  input  logic rst_n,
  input  logic uart_rx
);
  import tlul_pkg::*;
  import top_pkg::*;

  parameter int IMEM_BASE = 32'h0000_0000;
  parameter int DMEM_BASE = 32'h1000_0000;
  parameter int UART_BASE = 32'h2000_0000;

  localparam logic [31:0] UART_CTRL_OFF  = 32'h10;
  localparam logic [31:0] UART_WDATA_OFF = 32'h1c;

  logic uart_tx, uart_tx_en;

  tl_h2d_t tl_to_uart;
  tl_d2h_t tl_from_uart;

  // Wave-friendly aliases: flatten TL structs for GTKWave browsing
  // IMEM fetch channel (host -> device)
  logic        imem_a_valid;
  logic [2:0]  imem_a_opcode;
  logic [2:0]  imem_a_param;
  logic [top_pkg::TL_SZW-1:0] imem_a_size;
  logic [top_pkg::TL_AIW-1:0] imem_a_source;
  logic [top_pkg::TL_AW-1:0]  imem_a_address;
  logic [top_pkg::TL_DBW-1:0] imem_a_mask;
  logic [top_pkg::TL_DW-1:0]  imem_a_data;
  logic        imem_d_ready;

  // IMEM response channel (device -> host)
  logic        imem_d_valid;
  logic [2:0]  imem_d_opcode;
  logic [2:0]  imem_d_param;
  logic [top_pkg::TL_SZW-1:0] imem_d_size;
  logic [top_pkg::TL_AIW-1:0] imem_d_source;
  logic [top_pkg::TL_DIW-1:0] imem_d_sink;
  logic [top_pkg::TL_DW-1:0]  imem_d_data;
  logic        imem_d_error;

  // DMEM channel
  logic        dmem_a_valid;
  logic [2:0]  dmem_a_opcode;
  logic [top_pkg::TL_AW-1:0]  dmem_a_address;
  logic [top_pkg::TL_DBW-1:0] dmem_a_mask;
  logic [top_pkg::TL_DW-1:0]  dmem_a_data;
  logic        dmem_d_ready;
  logic        dmem_d_valid;
  logic [top_pkg::TL_DW-1:0]  dmem_d_data;
  logic        dmem_d_error;

  // UART TL channel (host->device and device->host)
  logic        uart_a_valid;
  logic [2:0]  uart_a_opcode;
  logic [2:0]  uart_a_param;
  logic [top_pkg::TL_SZW-1:0] uart_a_size;
  logic [top_pkg::TL_AIW-1:0] uart_a_source;
  logic [top_pkg::TL_AW-1:0]  uart_a_address;
  logic [top_pkg::TL_DBW-1:0] uart_a_mask;
  logic [top_pkg::TL_DW-1:0]  uart_a_data;
  logic        uart_d_ready;

  logic        uart_d_valid;
  logic [2:0]  uart_d_opcode;
  logic [2:0]  uart_d_param;
  logic [top_pkg::TL_SZW-1:0] uart_d_size;
  logic [top_pkg::TL_AIW-1:0] uart_d_source;
  logic [top_pkg::TL_DIW-1:0] uart_d_sink;
  logic [top_pkg::TL_DW-1:0]  uart_d_data;
  logic        uart_d_error;

`ifdef RVFI
  // Retire interface signals
  logic        rvfi_valid;
  logic [63:0] rvfi_order;
  logic [31:0] rvfi_insn;
  logic        rvfi_trap;
  logic        rvfi_halt;
  logic        rvfi_intr;
  logic [1:0]  rvfi_mode;
  logic [1:0]  rvfi_ixl;
  logic [4:0]  rvfi_rs1_addr;
  logic [4:0]  rvfi_rs2_addr;
  logic [4:0]  rvfi_rs3_addr;
  logic [31:0] rvfi_rs1_rdata;
  logic [31:0] rvfi_rs2_rdata;
  logic [31:0] rvfi_rs3_rdata;
  logic [4:0]  rvfi_rd_addr;
  logic [31:0] rvfi_rd_wdata;
  logic [31:0] rvfi_pc_rdata;
  logic [31:0] rvfi_pc_wdata;
  logic [31:0] rvfi_mem_addr;
  logic [3:0]  rvfi_mem_rmask;
  logic [3:0]  rvfi_mem_wmask;
  logic [31:0] rvfi_mem_rdata;
  logic [31:0] rvfi_mem_wdata;
  logic [31:0] rvfi_ext_pre_mip;
  logic [31:0] rvfi_ext_post_mip;
  logic        rvfi_ext_nmi;
  logic        rvfi_ext_nmi_int;
  logic        rvfi_ext_debug_req;
  logic        rvfi_ext_debug_mode;
  logic        rvfi_ext_rf_wr_suppress;
  logic [63:0] rvfi_ext_mcycle;
  logic [31:0] rvfi_ext_mhpmcounters [10];
  logic [31:0] rvfi_ext_mhpmcountersh [10];
  logic        rvfi_ext_ic_scr_key_valid;
  logic        rvfi_ext_irq_valid;
`endif

  // clock
  // initial clk = 1'b0;
  /* verilator lint_off STMTDLY */
  // always begin
  //   #5 clk = ~clk; // 100 MHz
  // end
  /* verilator lint_on STMTDLY */

  // reset (C++ harness drives release; keep defaults here)
  // initial begin
  //   rst_n = 1'b0;
  //   uart_rx = 1'b1; // UART idle high
  // end

  // DUT
  pure_ibex_uart_top dut (
    .clk_i(clk),
    .rst_ni(rst_n),

    .tl_to_uart_o(tl_to_uart),
    .tl_from_uart_o(tl_from_uart),

    .uart_rx_i(uart_rx),
    .uart_tx_o(uart_tx),
    .uart_tx_en_o(uart_tx_en)

`ifdef RVFI
    , .rvfi_valid(rvfi_valid), .rvfi_order(rvfi_order), .rvfi_insn(rvfi_insn),
      .rvfi_trap(rvfi_trap), .rvfi_halt(rvfi_halt), .rvfi_intr(rvfi_intr),
      .rvfi_mode(rvfi_mode), .rvfi_ixl(rvfi_ixl),
      .rvfi_rs1_addr(rvfi_rs1_addr), .rvfi_rs2_addr(rvfi_rs2_addr),
      .rvfi_rs3_addr(rvfi_rs3_addr), .rvfi_rs1_rdata(rvfi_rs1_rdata),
      .rvfi_rs2_rdata(rvfi_rs2_rdata), .rvfi_rs3_rdata(rvfi_rs3_rdata),
      .rvfi_rd_addr(rvfi_rd_addr), .rvfi_rd_wdata(rvfi_rd_wdata),
      .rvfi_pc_rdata(rvfi_pc_rdata), .rvfi_pc_wdata(rvfi_pc_wdata),
      .rvfi_mem_addr(rvfi_mem_addr), .rvfi_mem_rmask(rvfi_mem_rmask),
      .rvfi_mem_wmask(rvfi_mem_wmask), .rvfi_mem_rdata(rvfi_mem_rdata),
      .rvfi_mem_wdata(rvfi_mem_wdata),
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

  // Bind wave-friendly aliases to DUT internals (for GTKWave browsing)
  // IMEM host->device
  assign imem_a_valid   = dut.tl_imem_h2d.a_valid;
  assign imem_a_opcode  = dut.tl_imem_h2d.a_opcode;
  assign imem_a_param   = dut.tl_imem_h2d.a_param;
  assign imem_a_size    = dut.tl_imem_h2d.a_size;
  assign imem_a_source  = dut.tl_imem_h2d.a_source;
  assign imem_a_address = dut.tl_imem_h2d.a_address;
  assign imem_a_mask    = dut.tl_imem_h2d.a_mask;
  assign imem_a_data    = dut.tl_imem_h2d.a_data;
  assign imem_d_ready   = dut.tl_imem_h2d.d_ready;

  // IMEM device->host
  assign imem_d_valid   = dut.tl_imem_d2h.d_valid;
  assign imem_d_opcode  = dut.tl_imem_d2h.d_opcode;
  assign imem_d_param   = dut.tl_imem_d2h.d_param;
  assign imem_d_size    = dut.tl_imem_d2h.d_size;
  assign imem_d_source  = dut.tl_imem_d2h.d_source;
  assign imem_d_sink    = dut.tl_imem_d2h.d_sink;
  assign imem_d_data    = dut.tl_imem_d2h.d_data;
  assign imem_d_error   = dut.tl_imem_d2h.d_error;

  // DMEM host->device
  assign dmem_a_valid   = dut.tl_dmem_h2d.a_valid;
  assign dmem_a_opcode  = dut.tl_dmem_h2d.a_opcode;
  assign dmem_a_address = dut.tl_dmem_h2d.a_address;
  assign dmem_a_mask    = dut.tl_dmem_h2d.a_mask;
  assign dmem_a_data    = dut.tl_dmem_h2d.a_data;
  assign dmem_d_ready   = dut.tl_dmem_h2d.d_ready;
  // DMEM device->host
  assign dmem_d_valid   = dut.tl_dmem_d2h.d_valid;
  assign dmem_d_data    = dut.tl_dmem_d2h.d_data;
  assign dmem_d_error   = dut.tl_dmem_d2h.d_error;

  // UART host->device
  assign uart_a_valid   = dut.tl_to_uart.a_valid;
  assign uart_a_opcode  = dut.tl_to_uart.a_opcode;
  assign uart_a_param   = dut.tl_to_uart.a_param;
  assign uart_a_size    = dut.tl_to_uart.a_size;
  assign uart_a_source  = dut.tl_to_uart.a_source;
  assign uart_a_address = dut.tl_to_uart.a_address;
  assign uart_a_mask    = dut.tl_to_uart.a_mask;
  assign uart_a_data    = dut.tl_to_uart.a_data;
  assign uart_d_ready   = dut.tl_to_uart.d_ready;

  // UART device->host
  assign uart_d_valid   = dut.tl_from_uart.d_valid;
  assign uart_d_opcode  = dut.tl_from_uart.d_opcode;
  assign uart_d_param   = dut.tl_from_uart.d_param;
  assign uart_d_size    = dut.tl_from_uart.d_size;
  assign uart_d_source  = dut.tl_from_uart.d_source;
  assign uart_d_sink    = dut.tl_from_uart.d_sink;
  assign uart_d_data    = dut.tl_from_uart.d_data;
  assign uart_d_error   = dut.tl_from_uart.d_error;

  // waveform
  initial begin
    $dumpfile("mini.fst");
    $dumpvars(0, tb_pure_ibex_uart_top);
  end

  int fetch_cnt;
  always_ff @(posedge clk) if (rst_n && dut.tl_imem_h2d.a_valid && dut.tl_imem_d2h.a_ready) begin
    fetch_cnt++;
    if (fetch_cnt == 1) $display("[TB] First fetch @ 0x%08x", dut.tl_imem_h2d.a_address);
  end

  // Monitor Ibex instruction request (instr_req_o inside ibex_top)
  // Accessible via adapter input: u_instr2tl.req_i
  // int instr_req_cnt;
  // always_ff @(posedge clk) begin
  //   if (!rst_n) begin
  //     instr_req_cnt <= 0;
  //   end else if (dut.instr_rvalid) begin
  //     instr_req_cnt <= instr_req_cnt + 1;
  //     // Print the first few requests to avoid log spam
  //     if (instr_req_cnt < 100) begin
  //       $display("[TB] ibex instr_req_o #%0d @time %0t addr=0x%08x instr=0x%08x",
  //                instr_req_cnt, $time, dut.instr_addr,
  //                dut.instr_rdata);
  //     end
  //   end
  // end

`ifdef RVFI
  // Monitor retired instructions via RVFI
  int rvfi_cnt;
  always_ff @(posedge clk) begin
    if (!rst_n) begin
      rvfi_cnt <= 0;
    end else if (rvfi_valid) begin
      rvfi_cnt <= rvfi_cnt + 1;
      if (rvfi_cnt < 50) begin
        $display("[TB][RVFI] #%0d @time %0t pc=0x%08x -> 0x%08x insn=0x%08x rd=x%0d wdata=0x%08x trap=%0d intr=%0d",
                 rvfi_cnt, $time, rvfi_pc_rdata, rvfi_pc_wdata,
                 rvfi_insn, rvfi_rd_addr, rvfi_rd_wdata, rvfi_trap, rvfi_intr);
      end
    end
  end
`endif

  // Monitor UART TL host requests
  int uart_req_cnt;
  always_ff @(posedge clk) begin
    if (!rst_n) begin
      uart_req_cnt <= 0;
    end else if (uart_a_valid && tl_from_uart.a_ready) begin
      uart_req_cnt <= uart_req_cnt + 1;
      if (uart_req_cnt < 50) begin
        $display("[TB] UART TL req #%0d @time %0t opcode=%0d addr=0x%08x data=0x%08x mask=0x%x size=%0d", 
          uart_req_cnt, $time, uart_a_opcode, uart_a_address, uart_a_data, uart_a_mask, uart_a_size);
      end
    end
  end

  // ------------------------------------------------------------
  // “Cheat” console: print chars when SW writes UART.WDATA
  // UART.WDATA offset = 0x1c (from OT UART regs doc). :contentReference[oaicite:1]{index=1}
  // ------------------------------------------------------------
  localparam logic [31:0] UART_WDATA_ADDR = UART_BASE + UART_WDATA_OFF;
  localparam logic [31:0] UART_CTRL_ADDR  = UART_BASE + UART_CTRL_OFF;

  always_ff @(posedge clk) begin
    if (rst_n) begin
      if (tl_to_uart.a_valid && tl_from_uart.a_ready) begin
        // Writes can be PutFullData or PutPartialData
        if ((tl_to_uart.a_opcode == tlul_pkg::PutFullData ||
             tl_to_uart.a_opcode == tlul_pkg::PutPartialData) &&
            (tl_to_uart.a_address == UART_WDATA_ADDR)) begin
          $write("%c", tl_to_uart.a_data[7:0]);
        end

        // Optional: show when SW enables TX (CTRL.TX is bit0)
        if ((tl_to_uart.a_opcode == tlul_pkg::PutFullData ||
             tl_to_uart.a_opcode == tlul_pkg::PutPartialData) &&
            (tl_to_uart.a_address == UART_CTRL_ADDR)) begin
          $display("\n[TB] UART.CTRL write: 0x%08x (TX bit0=%0d)",
                   tl_to_uart.a_data, tl_to_uart.a_data[0]);
        end
      end
    end
  end

  // stop after some time
  // (timeout now handled in C++ harness)

endmodule
