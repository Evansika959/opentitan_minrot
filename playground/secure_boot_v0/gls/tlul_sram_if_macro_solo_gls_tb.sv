// tlul_sram_if_macro_solo_gls_tb.sv -- new file.
//
// Standalone GLS testbench for the ALREADY-INDEPENDENTLY-HARDENED
// tlul_sram_if_macro netlist (pd/macros/tlul_sram_if_macro/tlul_sram_if_macro.nl.v)
// -- nothing else: no ibex, no xbar, no PUF, no top_pd/top_pd_puf. Goal: find
// out, in isolation, whether one gate-level TL-UL <-> SRAM-macro adapter can
// do a basic write-then-read before blaming anything upstream.
//
// Why this exists: both integration-level GLS runs on record (gls_smoke_sim.log
// for top_pd, gls_puf_smoke_sim.log for top_pd_puf) FAILED -- the first hangs
// forever returning rdata=0xffffffff err=1, the second times out with zero
// UART bytes decoded. Neither failure has ever been isolated to a single
// block. rtl/tlul_sram_if_macro.sv's own header carries an unreconciled
// warning: "Read latency is 1 cycle (the macro's native synchronous read);
// note the behavioural models read in 2 cycles, so reconcile that before
// netlist co-sim." This testbench exists to directly measure that latency
// at the gate level and see whether tlul_adapter_sram (also inside this same
// netlist, synthesized together with the macro) actually handles it.
//
// Port-less, self-contained, self-clocking/self-resetting -- same convention
// as top_pd_puf_smoke_gls_tb.sv (verilator --binary, no custom C++ main
// needed; see that file's core for why reusing main_gls.cpp would be wrong
// for a port-less top module).
//
// Bit layout below is derived directly from tlul_pkg.sv's tl_h2d_t/tl_d2h_t
// struct field order (first-declared field = MSB, standard packed-struct
// flattening) and top_pkg.sv's TL_* width parameters, cross-checked against
// the actual flattened netlist port widths in tlul_sram_if_macro.nl.v
// (`input [113:0] tl_i; output [65:0] tl_o;` -- 114 and 66 bits, matching
// the struct field sums exactly). Do not import tlul_pkg here: the netlist's
// ports are plain flattened vectors, not struct-typed, so this testbench
// drives/reads them as plain vectors directly instead of relying on
// implicit struct<->vector casts at the port connection.
`timescale 1ns/1ps

module tlul_sram_if_macro_solo_gls_tb;

  // ---------------------------------------------------------------------
  // tl_h2d_t (h2d, 114 bits) field positions, MSB-first struct order:
  //   a_valid(1) a_opcode(3) a_param(3) a_size(2) a_source(8) a_address(32)
  //   a_mask(4) a_data(32) a_user(28) d_ready(1)
  // tl_d2h_t (d2h, 66 bits) field positions, MSB-first struct order:
  //   d_valid(1) d_opcode(3) d_param(3) d_size(2) d_source(8) d_sink(1)
  //   d_data(32) d_user(14) d_error(1) a_ready(1)
  // ---------------------------------------------------------------------
  localparam int H2D_W = 114;
  localparam int D2H_W = 66;

  typedef enum logic [2:0] { OP_PUT_FULL = 3'h0, OP_PUT_PARTIAL = 3'h1, OP_GET = 3'h4 } tl_a_op_e_local;
  typedef enum logic [2:0] { OP_ACK = 3'h0, OP_ACK_DATA = 3'h1 } tl_d_op_e_local;

  localparam logic [3:0] MUBI4_FALSE = 4'h9;

  function automatic logic [H2D_W-1:0] pack_h2d(
      logic        a_valid, tl_a_op_e_local a_opcode, logic [2:0] a_param,
      logic [1:0]  a_size,  logic [7:0]     a_source, logic [31:0] a_address,
      logic [3:0]  a_mask,  logic [31:0]    a_data,   logic        d_ready
  );
    logic [27:0] a_user;
    // rsvd=0, instr_type=MuBi4False (4'h9 -- NOT plain 0, which is an
    // invalid MuBi4 encoding and would trip instr_error in tlul_adapter_sram),
    // cmd_intg/data_intg=all-1 (blank/don't-check pattern, integrity checks
    // are disabled for this adapter instance per rtl/tlul_sram_if_macro.sv).
    a_user = {10'b0, 4'h9, 7'h7f, 7'h7f};
    pack_h2d = {a_valid, a_opcode, a_param, a_size, a_source, a_address, a_mask, a_data, a_user, d_ready};
  endfunction

  // Field extraction from the d2h flat vector.
  function automatic logic         d2h_d_valid(logic [D2H_W-1:0] v); d2h_d_valid = v[65]; endfunction
  function automatic logic [2:0]   d2h_d_opcode(logic [D2H_W-1:0] v); d2h_d_opcode = v[64:62]; endfunction
  function automatic logic [31:0]  d2h_d_data(logic [D2H_W-1:0] v); d2h_d_data = v[47:16]; endfunction
  function automatic logic         d2h_d_error(logic [D2H_W-1:0] v); d2h_d_error = v[1]; endfunction
  function automatic logic         d2h_a_ready(logic [D2H_W-1:0] v); d2h_a_ready = v[0]; endfunction

  // ---------------------------------------------------------------------
  // Clock / reset (self-contained, no ports)
  // ---------------------------------------------------------------------
  logic clk;
  logic rst_n;
  initial clk = 0;
  always #30 clk = ~clk;

  initial begin
    rst_n = 0;
    repeat (5) @(posedge clk);
    rst_n = 1;
  end

  // ---------------------------------------------------------------------
  // DUT: the already-independently-hardened netlist, nothing else.
  // ---------------------------------------------------------------------
  logic [H2D_W-1:0] tl_i;
  logic [D2H_W-1:0] tl_o;

  tlul_sram_if_macro dut (
    .clk_i       (clk),
    .rst_ni      (rst_n),
    .en_ifetch_i (MUBI4_FALSE),
    .tl_i        (tl_i),
    .tl_o        (tl_o)
  );

  // Raw diagnostic monitor: dump tl_o for the first 30 cycles after reset
  // release regardless of pass/fail, so a stuck-low a_ready can be told
  // apart from stuck-at-X, a late pulse, or a glitch -- info a bare
  // TIMEOUT message can't give you.
  int diag_cnt;
  initial diag_cnt = 0;
  always @(posedge clk) begin
    #1; // settle combinational logic before sampling, same as do_request's polling
    if (diag_cnt < 40) begin
      diag_cnt <= diag_cnt + 1;
      $display("[TLUL_SOLO_GLS][DIAG] t=%0t cyc=%0d rst_n=%b tl_o=0x%017h (a_ready=%b d_valid=%b) reqfifo_rvalid=%b sramreqfifo_depth=%b rspfifo_depth=%b rvalid=%b",
                $time, diag_cnt, rst_n, tl_o, tl_o[0], tl_o[65],
                dut.\u_adapt.reqfifo_rvalid ,
                dut.\u_adapt.u_sramreqfifo.depth_o ,
                dut.\u_adapt.u_rspfifo.depth_o ,
                dut.rvalid);
    end
  end

  // ---------------------------------------------------------------------
  // Minimal directed TL-UL master: PutFullData write, then Get read, of the
  // same address, back to back (no idle cycles in between) -- deliberately
  // the tightest-timing case, since the integration failure looked like a
  // handshake/latency problem, not a data-corruption problem.
  // ---------------------------------------------------------------------
  localparam logic [31:0] TEST_ADDR       = 32'h0000_0000;
  localparam logic [31:0] TEST_ADDR2      = 32'h0000_0004;
  localparam logic [31:0] TEST_WDATA      = 32'hCAFEF00D;
  localparam int          TIMEOUT_CYCLES  = 2000;

  int cyc;
  int a_accept_cyc, d_valid_cyc;
  bit pass_write, pass_read, pass_zero_before;
  logic [31:0] got_data;
  bit got_error;

  task automatic do_request(
      input tl_a_op_e_local opcode, input logic [31:0] addr,
      input logic [31:0] wdata, input logic [3:0] mask,
      output logic [31:0] rdata, output bit rd_error, output int accept_cyc, output int resp_cyc
  );
    bit accepted;
    accepted = 0;
    accept_cyc = -1;
    resp_cyc   = -1;
    // Change tl_i shortly AFTER the clock edge, never exactly on one --
    // the caller may resume this task right at a posedge (e.g. straight
    // out of a `repeat (N) @(posedge clk)`), and asserting a synchronous
    // input in the same instant as the sampling edge is a classic race
    // (simulator-order-dependent whether the DUT's flops see the new or
    // old value on that very edge). This bit us: a_ready/d_valid both
    // ended up reacting to the request on the SAME edge it was asserted,
    // one cycle earlier than intended, and this task's own two-phase wait
    // (accept, then separately wait for d_valid) missed the single-cycle
    // d_valid pulse because it had already come and gone before the
    // second wait loop started checking.
    #1;
    // Drive a_valid until a_ready seen (a_ready is d2h bit0, combinational
    // in this adapter per rtl -- gnt_i tied 1'b1 -- so this should accept
    // same cycle it's asserted; loop guards against it not doing so).
    tl_i = pack_h2d(1'b1, opcode, 3'b0, 2'b10 /*a_size=2 => 4 bytes*/, 8'h00,
                    addr, mask, wdata, 1'b1 /*d_ready always high*/);
    $display("[TLUL_SOLO_GLS][REQ] t=%0t asserting a_valid opcode=%0d addr=0x%08h", $time, opcode, addr);
    // Single unified poll loop, checking BOTH a_ready and d_valid on every
    // sampled edge without any gap. a_ready read immediately AFTER the
    // edge that accepts a request reflects the adapter's NEW (post-accept,
    // possibly already-busy-and-responding) state, not "just accepted" --
    // this adapter can complete accept+respond within a single edge when
    // starting from idle, so trying to deassert a_valid the instant
    // acceptance is first detected risks dropping it before/exactly as the
    // edge that actually needed it stable has occurred. Instead: keep
    // a_valid asserted through the accept-detected edge AND one extra full
    // cycle of margin before dropping it, while scanning every cycle
    // (gap-free) for d_valid the whole time -- can't miss a single-cycle
    // pulse regardless of exactly which edge it lands on.
    forever begin
      @(posedge clk);
      #1; // let combinational logic through several gate levels settle before sampling
      cyc++;
      if (!accepted && d2h_a_ready(tl_o)) begin
        accepted   = 1;
        accept_cyc = cyc;
      end
      if (accepted && cyc > accept_cyc) tl_i[113] = 1'b0; // one extra cycle of margin, then drop a_valid
      if (resp_cyc == -1 && d2h_d_valid(tl_o)) begin
        resp_cyc = cyc;
        rdata    = d2h_d_data(tl_o);
        rd_error = d2h_d_error(tl_o);
      end
      if (accepted && resp_cyc != -1) break;
      if (cyc > TIMEOUT_CYCLES) begin
        if (!accepted)
          $display("[TLUL_SOLO_GLS] TIMEOUT waiting for a_ready (opcode=%0d addr=0x%08h)", opcode, addr);
        else
          $display("[TLUL_SOLO_GLS] TIMEOUT waiting for d_valid after a_ready@cyc=%0d (opcode=%0d addr=0x%08h)", accept_cyc, opcode, addr);
        $display("[TLUL_SOLO_GLS] FAIL");
        $finish;
      end
    end
  endtask

  initial begin
    logic [31:0] rdata;
    bit rd_error;
    int t0, t1;

    cyc = 0;
    tl_i = '0;
    @(posedge rst_n);
    repeat (3) @(posedge clk); // a few idle cycles post-reset before first request

    // 1) Sanity read of an untouched word -- macro should report its reset
    //    (zero) content, not X's and not 0xffffffff (the integration-level
    //    failure signature).
    do_request(OP_GET, TEST_ADDR, 32'h0, 4'hF, rdata, rd_error, t0, t1);
    $display("[TLUL_SOLO_GLS] pre-write GET  addr=0x%08h -> data=0x%08h error=%0b  (a_ready@%0d d_valid@%0d, latency=%0d cyc)",
              TEST_ADDR, rdata, rd_error, t0, t1, t1 - t0);
    pass_zero_before = (rdata == 32'h0) && !rd_error;

    // 2) Write.
    do_request(OP_PUT_FULL, TEST_ADDR, TEST_WDATA, 4'hF, rdata, rd_error, t0, t1);
    $display("[TLUL_SOLO_GLS] PUT           addr=0x%08h  data=0x%08h error=%0b  (a_ready@%0d d_valid@%0d, latency=%0d cyc)",
              TEST_ADDR, TEST_WDATA, rd_error, t0, t1, t1 - t0);
    pass_write = !rd_error;

    // 3) Read back the SAME word immediately (back-to-back, no idle cycles
    //    -- the tight-timing case that would expose a 1-cycle-vs-2-cycle
    //    read-latency mismatch between tlul_adapter_sram and the real macro).
    do_request(OP_GET, TEST_ADDR, 32'h0, 4'hF, rdata, rd_error, t0, t1);
    $display("[TLUL_SOLO_GLS] post-write GET addr=0x%08h -> data=0x%08h error=%0b  (a_ready@%0d d_valid@%0d, latency=%0d cyc)",
              TEST_ADDR, rdata, rd_error, t0, t1, t1 - t0);
    got_data  = rdata;
    got_error = rd_error;
    pass_read = (rdata == TEST_WDATA) && !rd_error;

    // 4) Second address, to make sure address decode isn't accidentally
    //    aliasing back to TEST_ADDR.
    do_request(OP_GET, TEST_ADDR2, 32'h0, 4'hF, rdata, rd_error, t0, t1);
    $display("[TLUL_SOLO_GLS] other-addr GET addr=0x%08h -> data=0x%08h error=%0b  (a_ready@%0d d_valid@%0d, latency=%0d cyc)",
              TEST_ADDR2, rdata, rd_error, t0, t1, t1 - t0);

    $display("");
    if (pass_zero_before && pass_write && pass_read) begin
      $display("[TLUL_SOLO_GLS] PASS: gate-level tlul_sram_if_macro write+readback matched (wrote 0x%08h, read 0x%08h).", TEST_WDATA, got_data);
    end else begin
      $display("[TLUL_SOLO_GLS] FAIL: pre_write_zero=%0b write_ok=%0b read_match=%0b (wrote 0x%08h, read 0x%08h, error=%0b)",
                pass_zero_before, pass_write, pass_read, TEST_WDATA, got_data, got_error);
    end
    $finish;
  end

  // Backstop watchdog in absolute sim time, in case the directed sequence
  // itself gets stuck somewhere not covered by the per-request timeouts.
  initial begin
    #500000;
    $display("[TLUL_SOLO_GLS] FAIL: global watchdog timeout, sequence never reached $finish.");
    $finish;
  end

endmodule
