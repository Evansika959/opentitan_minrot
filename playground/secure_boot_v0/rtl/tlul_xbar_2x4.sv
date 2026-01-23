module tlul_xbar_2x4 #(
  // Memory map parameters
  parameter logic [31:0] ROM_BASE   = 32'h0000_0000,
  parameter logic [31:0] ROM_END    = 32'h0000_FFFF,

  parameter logic [31:0] ESRAM_BASE = 32'h1000_0000,
  parameter logic [31:0] ESRAM_END  = 32'h1000_FFFF,

  parameter logic [31:0] DSRAM_BASE = 32'h2000_0000,
  parameter logic [31:0] DSRAM_END  = 32'h2000_FFFF,

  parameter logic [31:0] UART_BASE  = 32'h3000_0000,
  parameter logic [31:0] UART_END   = 32'h3000_FFFF,

  // If 1: reject any Put* op from instr host with TL error response
  parameter bit ENFORCE_I_RO = 1'b1
) (
  input  logic clk_i,
  input  logic rst_ni,

  // Host 0: DATA
  input  tlul_pkg::tl_h2d_t h_d_i,
  output tlul_pkg::tl_d2h_t h_d_o,

  // Host 1: INSTR
  input  tlul_pkg::tl_h2d_t h_i_i,
  output tlul_pkg::tl_d2h_t h_i_o,

  // 4 devices out
  output tlul_pkg::tl_h2d_t dev0_o, // ROM
  input  tlul_pkg::tl_d2h_t dev0_i,

  output tlul_pkg::tl_h2d_t dev1_o, // DSRAM
  input  tlul_pkg::tl_d2h_t dev1_i,

  output tlul_pkg::tl_h2d_t dev2_o, // ESRAM
  input  tlul_pkg::tl_d2h_t dev2_i,

  output tlul_pkg::tl_h2d_t dev3_o, // UART
  input  tlul_pkg::tl_d2h_t dev3_i
);

  import tlul_pkg::*;

  function automatic logic in_range(input logic [31:0] a,
                                    input logic [31:0] lo,
                                    input logic [31:0] hi);
    return (a >= lo) && (a <= hi);
  endfunction

  function automatic logic [3:0] decode_dev(input logic [31:0] addr);
    logic [3:0] sel;
    sel = 4'b0000;
    if (in_range(addr, ROM_BASE,   ROM_END))   sel[0] = 1'b1;
    else if (in_range(addr, DSRAM_BASE, DSRAM_END)) sel[1] = 1'b1;
    else if (in_range(addr, ESRAM_BASE, ESRAM_END)) sel[2] = 1'b1;
    else if (in_range(addr, UART_BASE,  UART_END))  sel[3] = 1'b1;
    return sel;
  endfunction

  function automatic logic is_put(input tl_a_op_e op);
    return (op == PutFullData) || (op == PutPartialData);
  endfunction

  integer k;

  tl_d2h_t h_d_r, h_i_r;
  tl_h2d_t dev_h2d [4];
  tl_d2h_t dev_d2h [4];

  // Pack device ports into arrays
  always_comb begin
    dev_d2h[0] = dev0_i;
    dev_d2h[1] = dev1_i;
    dev_d2h[2] = dev2_i;
    dev_d2h[3] = dev3_i;
  end

  // Unpack arrays to outputs
  always_comb begin
    dev0_o = dev_h2d[0];
    dev1_o = dev_h2d[1];
    dev2_o = dev_h2d[2];
    dev3_o = dev_h2d[3];

    h_d_o  = h_d_r;
    h_i_o  = h_i_r;
  end

  // Error responder per host
  logic err_pend_d, err_pend_i;
  logic [2:0] err_size_d, err_size_i;
  logic [1:0] err_param_d, err_param_i;
  logic [8-1:0] err_source_d, err_source_i; // width from tlul_pkg
  tl_d_op_e err_d_opcode_d, err_d_opcode_i;

  // TL-UL D-channel opcode mapping:
  // For Get -> AccessAckData
  // For Put -> AccessAck
  function automatic tl_d_op_e a2d_opcode(input tl_a_op_e aop);
    if (aop == Get) return AccessAckData;
    else            return AccessAck;
  endfunction

  // Host default outputs
  always_comb begin
    h_d_r = TL_D2H_DEFAULT;
    h_i_r = TL_D2H_DEFAULT;

    // a_ready defaults to 0 unless granted to some device or error-accept
    h_d_r.a_ready = 1'b0;
    h_i_r.a_ready = 1'b0;

    // d_valid defaults to 0; will be driven by either device response or error responder
    h_d_r.d_valid = 1'b0;
    h_i_r.d_valid = 1'b0;
  end

  // Per-device outstanding tracking
  logic dev_busy [4];
  logic dev_owner [4]; // 0 = DATA host, 1 = INSTR host

  // Address decode (combinational)
  logic [3:0] sel_d, sel_i;
  assign sel_d = (h_d_i.a_valid) ? decode_dev(h_d_i.a_address) : 4'b0000;
  assign sel_i = (h_i_i.a_valid) ? decode_dev(h_i_i.a_address) : 4'b0000;

  // Optional: reject writes from instruction host
  logic i_is_bad_write;
  assign i_is_bad_write = ENFORCE_I_RO && h_i_i.a_valid && is_put(h_i_i.a_opcode);

  // Arbitration + A-channel routing
  // Fixed priority: DATA > INSTR per device.
  logic grant_d [4], grant_i [4];

  always_comb begin
    for (k = 0; k < 4; k++) begin
      grant_d[k] = 1'b0;
      grant_i[k] = 1'b0;
    end

    // If host has pending error response, don't accept new A (one-deep error queue)
    // Same for instr host.
    // Also don't accept instr writes if ENFORCE_I_RO.

    for (k = 0; k < 4; k++) begin
      if (!dev_busy[k]) begin
        // DATA host request to this device?
        if (!err_pend_d && h_d_i.a_valid && sel_d[k]) begin
          grant_d[k] = 1'b1;
        end else if (!err_pend_i && !i_is_bad_write && h_i_i.a_valid && sel_i[k]) begin
          // INSTR host only if DATA didn't take it
          grant_i[k] = 1'b1;
        end
      end
    end
  end

  // Connect granted host signals to the chosen device A-channel
  // Also route a_ready back to the granted host.
  always_comb begin
    for (k = 0; k < 4; k++) begin
      dev_h2d[k] = TL_H2D_DEFAULT;
      // d_ready must come from the owning host while busy
      dev_h2d[k].d_ready = 1'b0;
    end
    for (k = 0; k < 4; k++) begin
      if (grant_d[k]) begin
        dev_h2d[k] = h_d_i;
        // Host sees device a_ready
        h_d_r.a_ready = dev_d2h[k].a_ready;
        // If device a_ready=0, the host must keep a_valid asserted; we simply pass through.
      end else if (grant_i[k]) begin
        dev_h2d[k] = h_i_i;
        h_i_r.a_ready = dev_d2h[k].a_ready;
      end
    end
  end

  // Capture ownership when an A transaction is accepted by a device
  // and clear when the corresponding D response handshake completes.
  logic a_fire_d [4], a_fire_i [4];
  logic d_fire   [4];

  always_comb begin
    for (k = 0; k < 4; k++) begin
      a_fire_d[k] = grant_d[k] && h_d_i.a_valid && dev_d2h[k].a_ready;
      a_fire_i[k] = grant_i[k] && h_i_i.a_valid && dev_d2h[k].a_ready;
      d_fire[k]   = dev_d2h[k].d_valid && dev_h2d[k].d_ready; // dev_h2d[k].d_ready selected below
    end
  end

  // D-channel routing: only the owner gets d_valid/data, and only the owner drives d_ready.
  always_comb begin
    for (k = 0; k < 4; k++) begin
      if (dev_busy[k]) begin
        if (dev_owner[k] == 1'b0) begin
          // owner = DATA
          dev_h2d[k].d_ready = h_d_i.d_ready;
          h_d_r.d_valid      = dev_d2h[k].d_valid;
          h_d_r.d_opcode     = dev_d2h[k].d_opcode;
          h_d_r.d_param      = dev_d2h[k].d_param;
          h_d_r.d_size       = dev_d2h[k].d_size;
          h_d_r.d_source     = dev_d2h[k].d_source;
          h_d_r.d_sink       = dev_d2h[k].d_sink;
          h_d_r.d_data       = dev_d2h[k].d_data;
          h_d_r.d_user       = dev_d2h[k].d_user;
          h_d_r.d_error      = dev_d2h[k].d_error;
        end else begin
          // owner = INSTR
          dev_h2d[k].d_ready = h_i_i.d_ready;
          h_i_r.d_valid      = dev_d2h[k].d_valid;
          h_i_r.d_opcode     = dev_d2h[k].d_opcode;
          h_i_r.d_param      = dev_d2h[k].d_param;
          h_i_r.d_size       = dev_d2h[k].d_size;
          h_i_r.d_source     = dev_d2h[k].d_source;
          h_i_r.d_sink       = dev_d2h[k].d_sink;
          h_i_r.d_data       = dev_d2h[k].d_data;
          h_i_r.d_user       = dev_d2h[k].d_user;
          h_i_r.d_error      = dev_d2h[k].d_error;
        end
      end
    end
  end

  // Unmapped address + instr-write error responder
  // Accept A immediately and return an error response one cycle later.
  logic miss_d, miss_i;
  assign miss_d = h_d_i.a_valid && (sel_d == 4'b0000);
  assign miss_i = h_i_i.a_valid && ((sel_i == 4'b0000) || i_is_bad_write);

  // Handshake for accepting an error A (we "a_ready" it if no pending error)
  logic err_accept_d, err_accept_i;
  assign err_accept_d = miss_d && !err_pend_d;
  assign err_accept_i = miss_i && !err_pend_i;

  // Feed a_ready for error-accepted transactions (only if not also granted to device)
  // (If sel==0, it won't be granted anyway)
  always_comb begin
    if (err_accept_d) h_d_r.a_ready = 1'b1;
    if (err_accept_i) h_i_r.a_ready = 1'b1;
  end

  // Produce error D when pending and host is ready
  logic err_d_fire, err_i_fire;
  assign err_d_fire = err_pend_d && h_d_i.d_ready;
  assign err_i_fire = err_pend_i && h_i_i.d_ready;

  always_comb begin
    if (err_pend_d) begin
      h_d_r.d_valid  = 1'b1;
      h_d_r.d_opcode = err_d_opcode_d;
      h_d_r.d_param  = err_param_d;
      h_d_r.d_size   = err_size_d;
      h_d_r.d_source = err_source_d;
      h_d_r.d_sink   = '0;
      h_d_r.d_data   = 32'h0;
      h_d_r.d_user   = '0;
      h_d_r.d_error  = 1'b1;
    end
    if (err_pend_i) begin
      h_i_r.d_valid  = 1'b1;
      h_i_r.d_opcode = err_d_opcode_i;
      h_i_r.d_param  = err_param_i;
      h_i_r.d_size   = err_size_i;
      h_i_r.d_source = err_source_i;
      h_i_r.d_sink   = '0;
      h_i_r.d_data   = 32'h0;
      h_i_r.d_user   = '0;
      h_i_r.d_error  = 1'b1;
    end
  end

  // Sequential state updates
  always_ff @(posedge clk_i or negedge rst_ni) begin
    if (!rst_ni) begin
      for (int j = 0; j < 4; j++) begin
        dev_busy[j]  <= 1'b0;
        dev_owner[j] <= 1'b0;
      end
      err_pend_d <= 1'b0;
      err_pend_i <= 1'b0;
      err_size_d <= '0;
      err_size_i <= '0;
      err_param_d <= '0;
      err_param_i <= '0;
      err_source_d <= '0;
      err_source_i <= '0;
      err_d_opcode_d <= AccessAck;
      err_d_opcode_i <= AccessAck;
    end else begin
      // Device ownership capture on A accept
      for (int j = 0; j < 4; j++) begin
        if (a_fire_d[j]) begin
          dev_busy[j]  <= 1'b1;
          dev_owner[j] <= 1'b0;
        end else if (a_fire_i[j]) begin
          dev_busy[j]  <= 1'b1;
          dev_owner[j] <= 1'b1;
        end

        // Clear busy when D completes (device response handshake)
        if (dev_busy[j] && d_fire[j]) begin
          dev_busy[j] <= 1'b0;
        end
      end

      // Latch error requests
      if (err_accept_d) begin
        err_pend_d    <= 1'b1;
        err_size_d    <= h_d_i.a_size;
        err_param_d   <= h_d_i.a_param;
        err_source_d  <= h_d_i.a_source;
        err_d_opcode_d<= a2d_opcode(h_d_i.a_opcode);
      end
      if (err_accept_i) begin
        err_pend_i    <= 1'b1;
        err_size_i    <= h_i_i.a_size;
        err_param_i   <= h_i_i.a_param;
        err_source_i  <= h_i_i.a_source;
        err_d_opcode_i<= a2d_opcode(h_i_i.a_opcode);
      end

      // Clear pending error when delivered
      if (err_d_fire) err_pend_d <= 1'b0;
      if (err_i_fire) err_pend_i <= 1'b0;
    end
  end

endmodule
