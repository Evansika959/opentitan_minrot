// main_gls.cpp
//
// C++ driver for the GLS (gate-level simulation) of top_pd, modeled on
// tb/main.cpp (same clock/reset conventions) but targeting Vtop_pd_gls_tb.
// No DPI dump_esram hook here -- top_pd has no such debug export (it's a
// pin-level netlist), unlike rtl/top.sv.
#include "Vtop_pd_gls_tb.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include <iostream>

static vluint64_t main_time = 0;
static vluint64_t cycle = 0;
static const vluint64_t kClkPeriod = 100; // 10 MHz if 1 time unit = 1 ns

double sc_time_stamp() { return main_time; }

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);

  Vtop_pd_gls_tb top;
  VerilatedFstC tfp;
  top.trace(&tfp, 99);
  tfp.open("secure_boot_v0_gls.fst");

  bool announced_start = false;

  while (!Verilated::gotFinish()) {
    // clock: 10 MHz -> 100 time units per cycle (assuming 1 time unit = 1 ns)
    top.clk = ((main_time % kClkPeriod) < (kClkPeriod / 2)) ? 1 : 0;

    // keep UART RX idle high
    top.uart_rx = 1;

    // deassert reset after 50 clock cycles
    cycle = main_time / kClkPeriod;
    top.rst_n = (cycle >= 50);

    if (!announced_start && top.rst_n) {
      std::cout << "[CPP] GLS simulation starts! reset released at cycle " << (unsigned long)cycle << std::endl;
      announced_start = true;
    }

    top.eval();
    tfp.dump(main_time);

    if (cycle >= 500000) {
      std::cout << "\n[CPP] Stopping GLS simulation at cycle " << (unsigned long)cycle << std::endl;
      break;
    }

    main_time++;
  }

  tfp.close();
  return 0;
}
