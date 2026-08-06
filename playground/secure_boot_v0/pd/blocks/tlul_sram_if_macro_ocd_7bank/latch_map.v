// GF180 latch techmap for LibreLane SYNTH_LATCH_MAP.
// The gf180mcuD PDK references a latch_map.v that doesn't ship, so Yosys can't map
// the D-latch from OpenTitan's prim_clock_gating -> "1 Unmapped Yosys instance".
// This maps the generic Yosys latches to gf180mcu_fd_sc_mcu7t5v0__latq_1:
//   latq_1: Q = D while E = 1 (active-high enable), holds while E = 0.  Pins: D, E, Q.

module \$_DLATCH_P_ (E, D, Q);   // transparent when E = 1
  input  E, D;
  output Q;
  gf180mcu_fd_sc_mcu7t5v0__latq_1 _TECHMAP_REPLACE_ (.D(D), .E(E), .Q(Q));
endmodule

module \$_DLATCH_N_ (E, D, Q);   // transparent when E = 0 -> invert enable
  input  E, D;
  output Q;
  wire en;
  gf180mcu_fd_sc_mcu7t5v0__inv_1  _en_inv          (.I(E), .ZN(en));
  gf180mcu_fd_sc_mcu7t5v0__latq_1 _TECHMAP_REPLACE_ (.D(D), .E(en), .Q(Q));
endmodule
