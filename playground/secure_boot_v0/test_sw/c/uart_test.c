#include <stdint.h>

#define UART_BASE      0x00030000u
#define UART_CTRL_OFF  0x10u
#define UART_STATUS_OFF 0x14u
#define UART_WDATA_OFF 0x1cu

#define UART_STATUS_TXFULL_MASK 0x1u

static inline void uart_putc(char c) {
  volatile uint32_t *const ctrl   = (uint32_t *)(UART_BASE + UART_CTRL_OFF);
  volatile uint32_t *const status = (uint32_t *)(UART_BASE + UART_STATUS_OFF);
  volatile uint32_t *const wdata  = (uint32_t *)(UART_BASE + UART_WDATA_OFF);

  // One-time init: enable TX and set NCO for 10MHz -> 115200 baud (0x2F30)
  static int initialized;
  if (!initialized) {
    *ctrl = (0x2F30u << 16) | 0x1u; // NCO[31:16] + TX_EN
    initialized = 1;
  }

  // Wait for space in TX FIFO
  while ((*status & UART_STATUS_TXFULL_MASK) != 0) {
    // spin
  }

  // Write byte
  uint32_t byte = (uint8_t)c;  // keeps it in a register
  *wdata = byte;
}

int main(void) {
  const char *msg = "helloworld";
  for (const char *p = msg; *p; ++p) {
    uart_putc(*p);
  }
  while (1) {
    // idle
  }
  return 0;
}