
module top_tb(
  input  logic clk,
  input  logic rst_n,
  input  logic uart_rx
);
  import tlul_pkg::*;
  import top_pkg::*;

  parameter int UART_BASE = 32'h0003_0000;
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

  // DMEM channel (host -> device / device -> host)
  logic        dmem_a_valid;
  logic [2:0]  dmem_a_opcode;
  logic [top_pkg::TL_AW-1:0]  dmem_a_address;
  logic [top_pkg::TL_SZW-1:0] dmem_a_size;
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

  logic        dsram_a_valid;
  logic [2:0]  dsram_a_opcode;
  logic [2:0]  dsram_a_param;
  logic [top_pkg::TL_SZW-1:0] dsram_a_size;
  logic [top_pkg::TL_AIW-1:0] dsram_a_source;
  logic [top_pkg::TL_AW-1:0]  dsram_a_address;
  logic [top_pkg::TL_DBW-1:0] dsram_a_mask;
  logic [top_pkg::TL_DW-1:0]  dsram_a_data;
  logic        dsram_d_ready;

  logic       dsram_d_valid;
  logic [top_pkg::TL_DW-1:0] dsram_d_data;
  logic       dsram_d_error;

  logic        esram_a_valid;
  logic [2:0]  esram_a_opcode;
  logic [2:0]  esram_a_param;
  logic [top_pkg::TL_SZW-1:0] esram_a_size;
  logic [top_pkg::TL_AIW-1:0] esram_a_source;
  logic [top_pkg::TL_AW-1:0]  esram_a_address;
  logic [top_pkg::TL_DBW-1:0] esram_a_mask;
  logic [top_pkg::TL_DW-1:0]  esram_a_data;
  logic        esram_d_ready;

  logic       esram_d_valid;
  logic [top_pkg::TL_DW-1:0] esram_d_data;
  logic       esram_d_error;

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

  // Simple RV32I/M decoder for printing mnemonics in the TB
  function automatic string rv32_decode(input logic [31:0] insn);
    logic [6:0] opc; logic [2:0] f3; logic [6:0] f7; logic [4:0] rd, rs1, rs2;
    opc = insn[6:0]; f3 = insn[14:12]; f7 = insn[31:25];
    rd = insn[11:7]; rs1 = insn[19:15]; rs2 = insn[24:20];
    case (opc)
      7'h37: rv32_decode = $sformatf("lui x%0d,0x%05x", rd, insn[31:12]);
      7'h17: rv32_decode = $sformatf("auipc x%0d,0x%05x", rd, insn[31:12]);
      7'h6f: rv32_decode = $sformatf("jal x%0d,%0d", rd, $signed({insn[31],insn[19:12],insn[20],insn[30:21],1'b0}));
      7'h67: rv32_decode = $sformatf("jalr x%0d,%0d(x%0d)", rd, $signed(insn[31:20]), rs1);
      7'h63: begin
        string bname; case (f3)
          3'b000: bname = "beq"; 3'b001: bname = "bne";
          3'b100: bname = "blt"; 3'b101: bname = "bge";
          3'b110: bname = "bltu";3'b111: bname = "bgeu";
          default: bname = "b?"; endcase
        rv32_decode = $sformatf("%s x%0d,x%0d,%0d", bname, rs1, rs2,
          $signed({insn[31],insn[7],insn[30:25],insn[11:8],1'b0}));
      end
      7'h03: begin
        string lname; case (f3)
          3'b000: lname = "lb"; 3'b001: lname = "lh"; 3'b010: lname = "lw";
          3'b100: lname = "lbu";3'b101: lname = "lhu"; default: lname = "l?"; endcase
        rv32_decode = $sformatf("%s x%0d,%0d(x%0d)", lname, rd, $signed(insn[31:20]), rs1);
      end
      7'h23: begin
        string sname; case (f3)
          3'b000: sname = "sb"; 3'b001: sname = "sh"; 3'b010: sname = "sw";
          default: sname = "s?"; endcase
        rv32_decode = $sformatf("%s x%0d,%0d(x%0d)", sname, rs2,
          $signed({insn[31:25],insn[11:7]}), rs1);
      end
      7'h13: begin
        string iname; case (f3)
          3'b000: iname = "addi"; 3'b010: iname = "slti"; 3'b011: iname = "sltiu";
          3'b100: iname = "xori"; 3'b110: iname = "ori"; 3'b111: iname = "andi";
          3'b001: iname = (f7==7'h00) ? "slli" : "sll?";
          3'b101: iname = (f7==7'h20) ? "srai" : "srli";
          default: iname = "i?"; endcase
        if (f3 inside {3'b001,3'b101})
          rv32_decode = $sformatf("%s x%0d,x%0d,%0d", iname, rd, rs1, insn[24:20]);
        else
          rv32_decode = $sformatf("%s x%0d,x%0d,%0d", iname, rd, rs1, $signed(insn[31:20]));
      end
      7'h33: begin
        string rname; case ({f7,f3})
          {7'h00,3'b000}: rname="add";   {7'h20,3'b000}: rname="sub";
          {7'h00,3'b001}: rname="sll";   {7'h00,3'b010}: rname="slt";
          {7'h00,3'b011}: rname="sltu";  {7'h00,3'b100}: rname="xor";
          {7'h00,3'b101}: rname="srl";   {7'h20,3'b101}: rname="sra";
          {7'h00,3'b110}: rname="or";    {7'h00,3'b111}: rname="and";
          {7'h01,3'b000}: rname="mul";   {7'h01,3'b001}: rname="mulh";
          {7'h01,3'b010}: rname="mulhsu";{7'h01,3'b011}: rname="mulhu";
          {7'h01,3'b100}: rname="div";   {7'h01,3'b101}: rname="divu";
          {7'h01,3'b110}: rname="rem";   {7'h01,3'b111}: rname="remu";
          default: rname="r?"; endcase
        rv32_decode = $sformatf("%s x%0d,x%0d,x%0d", rname, rd, rs1, rs2);
      end
      7'h0f: rv32_decode = (f3==3'b001) ? "fence.i" : "fence";
      7'h73: begin
        if (f3==3'b000) begin
          if (insn[31:20]==12'h000) rv32_decode = "ecall";
          else if (insn[31:20]==12'h001) rv32_decode = "ebreak";
          else rv32_decode = "system";
        end else begin
          string cname; case (f3)
            3'b001: cname="csrrw"; 3'b010: cname="csrrs"; 3'b011: cname="csrrc";
            3'b101: cname="csrrwi";3'b110: cname="csrrsi";3'b111: cname="csrrci";
            default: cname="csr?"; endcase
          if (f3>=3'b101)
            rv32_decode = $sformatf("%s x%0d,0x%03x,%0d", cname, rd, insn[31:20], rs1);
          else
            rv32_decode = $sformatf("%s x%0d,0x%03x,x%0d", cname, rd, insn[31:20], rs1);
        end
      end
      default: rv32_decode = $sformatf("unknown 0x%08x", insn);
    endcase
  endfunction
`endif

  // DUT
  top dut (
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
  assign dmem_a_size    = dut.tl_dmem_h2d.a_size;
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

  // D-SRAM host to device signals
  assign dsram_a_valid   = dut.tl_to_dmem_sram.a_valid;
  assign dsram_a_opcode  = dut.tl_to_dmem_sram.a_opcode;
  assign dsram_a_param   = dut.tl_to_dmem_sram.a_param;
  assign dsram_a_size    = dut.tl_to_dmem_sram.a_size;
  assign dsram_a_source  = dut.tl_to_dmem_sram.a_source;
  assign dsram_a_address = dut.tl_to_dmem_sram.a_address;
  assign dsram_a_mask    = dut.tl_to_dmem_sram.a_mask;
  assign dsram_a_data    = dut.tl_to_dmem_sram.a_data;
  assign dsram_d_ready   = dut.tl_to_dmem_sram.d_ready;
  // D-SRAM device->host
  assign dsram_d_valid   = dut.tl_from_dmem_sram.d_valid;
  assign dsram_d_data    = dut.tl_from_dmem_sram.d_data;
  assign dsram_d_error   = dut.tl_from_dmem_sram.d_error;

  // E-SRAM host to device signals
  assign esram_a_valid   = dut.tl_to_esram.a_valid;
  assign esram_a_opcode  = dut.tl_to_esram.a_opcode;
  assign esram_a_param   = dut.tl_to_esram.a_param;
  assign esram_a_size    = dut.tl_to_esram.a_size;
  assign esram_a_source  = dut.tl_to_esram.a_source;
  assign esram_a_address = dut.tl_to_esram.a_address;
  assign esram_a_mask    = dut.tl_to_esram.a_mask;
  assign esram_a_data    = dut.tl_to_esram.a_data;
  assign esram_d_ready   = dut.tl_to_esram.d_ready;
  // E-SRAM device->host
  assign esram_d_valid   = dut.tl_from_esram.d_valid;
  assign esram_d_data    = dut.tl_from_esram.d_data;
  assign esram_d_error   = dut.tl_from_esram.d_error;

  // UART line listener: decode uart_tx into bytes using system clock (~10MHz) and expected baud (~115200).
  // Assumes UART NCO set to 0x2F30, giving ~87 clk cycles per bit.
  localparam int UART_BIT_TICKS = 87;
  typedef enum logic [1:0] {UART_IDLE, UART_START, UART_DATA, UART_STOP} uart_rx_state_e;
  uart_rx_state_e uart_rx_state;
  int uart_tick_cnt;
  int uart_bit_idx;
  byte uart_shift;

  always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      uart_rx_state <= UART_IDLE;
      uart_tick_cnt <= 0;
      uart_bit_idx  <= 0;
      uart_shift    <= 8'h00;
    end else begin
      case (uart_rx_state)
        UART_IDLE: begin
          uart_tick_cnt <= 0;
          uart_bit_idx  <= 0;
          if (uart_tx_en && uart_tx == 1'b0) begin
            uart_rx_state <= UART_START; // detect start bit
            uart_tick_cnt <= 1;
          end
        end
        UART_START: begin
          uart_tick_cnt <= uart_tick_cnt + 1;
          if (uart_tick_cnt >= (UART_BIT_TICKS/2)) begin
            if (uart_tx == 1'b0) begin
              uart_rx_state <= UART_DATA;
              uart_tick_cnt <= 0;
              uart_bit_idx  <= 0;
            end else begin
              uart_rx_state <= UART_IDLE; // false start
            end
          end
        end
        UART_DATA: begin
          uart_tick_cnt <= uart_tick_cnt + 1;
          if (uart_tick_cnt >= UART_BIT_TICKS) begin
            uart_tick_cnt <= 0;
            uart_shift[uart_bit_idx] <= uart_tx;
            uart_bit_idx <= uart_bit_idx + 1;
            if (uart_bit_idx == 7) uart_rx_state <= UART_STOP;
          end
        end
        UART_STOP: begin
          uart_tick_cnt <= uart_tick_cnt + 1;
          if (uart_tick_cnt >= UART_BIT_TICKS) begin
            uart_rx_state <= UART_IDLE;
            uart_tick_cnt <= 0;
            $display("[TB][UART_RX] byte=0x%02x ('%s') @%0t",
                     uart_shift,
                     (uart_shift >= 8'h20 && uart_shift <= 8'h7e) ? {uart_shift} : "?",
                     $time);
          end
        end
      endcase
    end
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
      if (rvfi_cnt < 32'hFFFFFFFF) begin
        $display("[TB][RVFI] #%0d @time %0t pc=0x%08x -> 0x%08x insn=0x%08x (%s) rd=x%0d wdata=0x%08x trap=%0d intr=%0d",
                 rvfi_cnt, $time, rvfi_pc_rdata, rvfi_pc_wdata,
                 rvfi_insn, rv32_decode(rvfi_insn),
                 rvfi_rd_addr, rvfi_rd_wdata, rvfi_trap, rvfi_intr);
      end
    end
  end
`endif

//   // Monitor UART TL host requests
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

  // Flag TL-UL errors coming back from UART
  int uart_err_cnt;
  always_ff @(posedge clk) begin
    if (!rst_n) begin
      uart_err_cnt <= 0;
    end else if (uart_d_valid && uart_d_error) begin
      uart_err_cnt <= uart_err_cnt + 1;
    end
    if (rst_n && uart_d_valid && uart_d_error && uart_err_cnt < 5) begin
      $display("[TB][UART][ERR] @time %0t opcode=%0d sink=%0d data=0x%08x", $time, uart_d_opcode, uart_d_sink, uart_d_data);
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

  // C++ harness hook: dump exec SRAM (u_esram inside DUT) to hex
  function automatic void dump_esram(input string path);
    begin
      dut.dump_esram(path);
    end
  endfunction
  export "DPI-C" function dump_esram;

endmodule
