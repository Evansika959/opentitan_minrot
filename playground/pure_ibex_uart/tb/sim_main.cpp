#include "Vtb_pure_ibex_uart_top.h"
#include "verilated.h"
#include "verilated_fst_c.h"

static vluint64_t main_time = 0;

// track full clock cycles (posedge count)
static vluint64_t cycle = 0;
static const vluint64_t kClkPeriod = 100; // time units per full cycle (10 MHz if 1 time unit = 1 ns)

double sc_time_stamp() { return main_time; }

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);

  Vtb_pure_ibex_uart_top top;
  VerilatedFstC tfp;
  top.trace(&tfp, 99);
  tfp.open("mini.fst");

  bool announced_start = false;

  while (!Verilated::gotFinish()) {
    // clock: 10 MHz -> 100 time units per cycle (assuming 1 time unit = 1 ns)
    top.clk = ((main_time % kClkPeriod) < (kClkPeriod / 2)) ? 1 : 0;

    // keep UART RX idle high
    top.uart_rx = 1;

    // deassert reset after 50 clock cycles (moved from SV tb)
    cycle = main_time / kClkPeriod;  // full cycles elapsed
    top.rst_n = (cycle >= 50);

    if (!announced_start && top.rst_n) {
      VL_PRINTF("[CPP] Simulation starts! reset released at cycle %llu\n", cycle);
      announced_start = true;
    }

    top.eval();
    tfp.dump(main_time);

    // stop after ~200k cycles (moved from SV tb)
    if (cycle >= 200000) {
      VL_PRINTF("\n[CPP] Timeout after %llu cycles\n", cycle);
      break;
    }

    main_time++;
  }

  tfp.close();
  return 0;
}
