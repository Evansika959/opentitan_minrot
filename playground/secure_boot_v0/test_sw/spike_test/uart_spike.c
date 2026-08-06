// uart_spike.c -- spike-only copy of test_sw/c/utils/uart.c, pointed at
// uart_spike.h instead. Logic is byte-for-byte identical to the real
// uart.c; only the included header (and therefore UART_BASE) differs.
#include "uart_spike.h"

void uart_putc(char c) {
  volatile uint32_t *const ctrl   = (uint32_t *)(UART_BASE + UART_CTRL_OFF);
  volatile uint32_t *const status = (uint32_t *)(UART_BASE + UART_STATUS_OFF);
  volatile uint32_t *const wdata  = (uint32_t *)(UART_BASE + UART_WDATA_OFF);

  static int initialized;
  if (!initialized) {
    *ctrl = (0x2F30u << 16) | 0x1u; // NCO[31:16] + TX_EN
    initialized = 1;
  }

  while ((*status & UART_STATUS_TXFULL_MASK) != 0) {
    // spin
  }

  *wdata = (uint8_t)c;
}
