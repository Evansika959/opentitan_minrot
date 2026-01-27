#include "Vtop_tb.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include "verilated_dpi.h"

extern "C" void dump_esram(const char* path);

static vluint64_t main_time = 0;

// track full clock cycles (posedge count)
static vluint64_t cycle = 0;
static const vluint64_t kClkPeriod = 100; // time units per full cycle (10 MHz if 1 time unit = 1 ns)

double sc_time_stamp() { return main_time; }

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Verilated::traceEverOn(true);

  Vtop_tb top;
  VerilatedFstC tfp;
  top.trace(&tfp, 99);
  tfp.open("secure_boot_v0.fst");

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
      VL_PRINTF("[CPP] Simulation starts! reset released at cycle %lu\n", (unsigned long)cycle);
      announced_start = true;
    }

    top.eval();
    tfp.dump(main_time);

    if (cycle >= 50000) {
      VL_PRINTF("\n[CPP] Timeout after %lu cycles\n", (unsigned long)cycle);
      break;
    }

    main_time++;
  }

  // Set SV scope and dump exec SRAM contents after simulation completes via DPI-exported function
  svSetScope(svGetScopeFromName("TOP.top_tb"));
  dump_esram("esram_dump.hex");

  tfp.close();
  return 0;
}
