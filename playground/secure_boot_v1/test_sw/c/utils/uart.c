#include "uart.h"

void uart_putc(char c) {
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
  *wdata = (uint8_t)c;
}

void uart_puts(const char *s) {
  while (*s) {
    uart_putc(*s++);
  }
}

void uart_put_hex4(uint8_t v) {
  const char hex_chars[] = "0123456789ABCDEF";
  uart_putc(hex_chars[v & 0xF]);
}

void uart_put_hex8(uint8_t v) {
  const char hex_chars[] = "0123456789ABCDEF";
  uart_putc(hex_chars[(v >> 4) & 0xF]);
  uart_putc(hex_chars[v & 0xF]);
}

void uart_put_hex32(uint32_t v) {
  uart_put_hex8((v >> 24) & 0xFF);
  uart_put_hex8((v >> 16) & 0xFF);
  uart_put_hex8((v >> 8) & 0xFF);
  uart_put_hex8(v & 0xFF);
}