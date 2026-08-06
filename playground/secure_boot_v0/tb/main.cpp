#include "Vtop_tb.h"
#include "Vtop_tb___024root.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include "verilated_dpi.h"
#include <iostream>
#include <ostream>

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
  vluint64_t post_reset_cycles = 0;

  while (!Verilated::gotFinish()) {
    // clock: 10 MHz -> 100 time units per cycle (assuming 1 time unit = 1 ns)
    top.clk = ((main_time % kClkPeriod) < (kClkPeriod / 2)) ? 1 : 0;

    // keep UART RX idle high
    top.uart_rx = 1;

    // deassert reset after 50 clock cycles
    cycle = main_time / kClkPeriod;  
    top.rst_n = (cycle >= 50);

    if (!announced_start && top.rst_n) {
      std::cout << "[CPP] Simulation starts! reset released at cycle " << (unsigned long)cycle << std::endl;
      announced_start = true;
    }

    top.eval();
    tfp.dump(main_time);

    // Track cycles after reset release to pinpoint when the boot sequence stalls or crashes
    if (top.rst_n) {
      post_reset_cycles++;
      
      // If we are around the time the 'P' character prints and it starts looping into illegal instructions,
      // let's log milestone cycles to see how far the execution gets before crashing.
      if (post_reset_cycles == 50000 || post_reset_cycles == 100000 || post_reset_cycles == 200000) {
        std::cout << "[CPP CHECK] Active at post-reset cycle " << (unsigned long)post_reset_cycles << std::endl;
      }
    }

    if (cycle >= 500000) { // Shortened timeout slightly to catch the crash window faster
      std::cout << "\n[CPP] Stopping simulation for inspection at cycle " << (unsigned long)cycle << std::endl;
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
