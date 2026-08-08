`timescale 1ns/1ps
module tb_top;
  logic clk;
  logic rst_n;
  logic uart_tx;
  always #10 clk = ~clk;

  top dut (
    .clk_i     (clk),
    .rst_ni    (rst_n),
    .uart_tx_o (uart_tx)
  );

  // --- Memory preload for the hard-macro path ---
  // The real gf180 SRAM macro has no MemInitFile support (unlike the
  // behavioural prim_ram_1p) -- so we load the hex images into plain
  // arrays here, then hierarchically force each byte into the 4 real
  // byte-lane macro instances before releasing reset.
  logic [31:0] imem_words [0:255];
  logic [31:0] dmem_words [0:255];

  initial begin
    integer i;
    $readmemh("/foss/designs/opentitan_minrot_nix/playground/secure_boot_v0/test_sw/hex/rom.imem.hex", imem_words);
    $readmemh("/foss/designs/opentitan_minrot_nix/playground/secure_boot_v0/test_sw/hex/rom_with_image.dmem.hex", dmem_words);

    for (i = 0; i < 256; i = i + 1) begin
      dut.u_esram.u_mem.gen_byte[0].u_macro.mem[i] = imem_words[i][7:0];
      dut.u_esram.u_mem.gen_byte[1].u_macro.mem[i] = imem_words[i][15:8];
      dut.u_esram.u_mem.gen_byte[2].u_macro.mem[i] = imem_words[i][23:16];
      dut.u_esram.u_mem.gen_byte[3].u_macro.mem[i] = imem_words[i][31:24];

      dut.u_dmem.u_mem.gen_byte[0].u_macro.mem[i] = dmem_words[i][7:0];
      dut.u_dmem.u_mem.gen_byte[1].u_macro.mem[i] = dmem_words[i][15:8];
      dut.u_dmem.u_mem.gen_byte[2].u_macro.mem[i] = dmem_words[i][23:16];
      dut.u_dmem.u_mem.gen_byte[3].u_macro.mem[i] = dmem_words[i][31:24];
    end

    $display("[TB] Preloaded esram/dmem macro arrays from hex images");
  end

  initial begin
  //  force dut.u_ibex.fetch_enable_i = 4'h9;
  //  force dut.u_ibex.boot_addr_i    = 32'h00000000;
  //  force dut.u_ibex.test_en_i      = 1'b0;
  end

  initial begin
    clk   = 0;
    rst_n = 0;
    $dumpfile("sim_top.fst");
    $dumpvars(0, tb_top);
    $display("------------------------------------------------------------------");
    $display("[TB] Starting Secure Boot OpenTitan Top Simulation");
    $display("------------------------------------------------------------------");
    #200;
    rst_n = 1;
    $display("[TB] Reset released, monitoring execution...\n");
    #2_000_000;
    $display("\n--------------------------------------------------");
    $display("[TB ERROR] Simulation Timed Out!");
    $display("--------------------------------------------------");
    $fatal(1);
  end

  // only print when the fetch address actually changes, not every cycle
  logic [31:0] last_addr;
  initial last_addr = 32'hFFFFFFFF;
  always @(posedge clk) begin
  if (rst_n && dut.tl_imem_h2d.a_valid)
    $display("[XBAR CHECK] Time=%0t addr=0x%08h a_ready=%b",
             $time, dut.tl_imem_h2d.a_address, dut.tl_imem_d2h.a_ready);
  end

  always @(posedge clk) begin
    if (rst_n)
      $display("[BOOT ADDR CHECK] boot_addr_i=0x%08h", dut.u_ibex.boot_addr_i);
  end

  always @(posedge clk) begin
    if (rst_n && dut.u_data2tl.tl_o.a_valid)
      $display("[DMEM REQ] Time=%0t addr=0x%08h we=%b wdata=0x%08h",
               $time, dut.u_data2tl.tl_o.a_address, dut.data_we, dut.data_wdata);
    if (rst_n && dut.data_rvalid)
      $display("[DMEM RESP] Time=%0t rdata=0x%08h", $time, dut.data_rdata);
  end

  always @(posedge clk) begin
    if (rst_n && dut.u_ibex.instr_req_o && (dut.u_ibex.instr_addr_o !== last_addr)) begin
      $display("[TOP FETCH] Time=%0t ns | Addr = 0x%08h | gnt = %b",
               $time, dut.u_ibex.instr_addr_o, dut.u_ibex.instr_gnt_i);
      last_addr <= dut.u_ibex.instr_addr_o;
    end
  end

  // Monitor activity
  always @(posedge clk) begin
    if (rst_n) begin
      if (dut.u_data2tl.tl_o.a_valid && (dut.u_data2tl.tl_o.a_address == 32'h4000_0000)) begin
        if (dut.u_data2tl.tl_o.a_data == 32'h0000_0001) begin
          $display("\n--------------------------------------------------");
          $display("[TB SUCCESS] Firmware reported: PASS!");
          $display("--------------------------------------------------");
          $finish;
        end else if (dut.u_data2tl.tl_o.a_data == 32'hdead_dead) begin
          $display("\n--------------------------------------------------");
          $display("[TB FAILURE] Firmware reported: FAIL!");
          $display("--------------------------------------------------");
          $fatal(1);
        end
      end
    end
  end

  // UART Sniffer
  parameter int BaudRate = 115200;
  parameter int BitPeriod = 1_000_000_000 / BaudRate;
  logic [7:0] rx_byte;
  initial begin
    rx_byte = 0;
    forever begin
      @(negedge uart_tx);
      #(BitPeriod / 2);
      if (uart_tx == 1'b0) begin
        for (int i = 0; i < 8; i++) begin
          #(BitPeriod);
          rx_byte[i] = uart_tx;
        end
        #(BitPeriod);
        $write("%c", rx_byte);
        $fflush();
      end
    end
  end
endmodule
