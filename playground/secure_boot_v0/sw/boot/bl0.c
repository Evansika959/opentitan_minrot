// bl0.c
#include <stdint.h>

// UART stubs (replace with your known-good)

#include "../utils/uart.h"

static void uart_puts(const char *s);

int main(void) {
  uart_putc('B');
  while (1) { __asm__ volatile("wfi"); }
}

// ====== UART ======
static void uart_puts(const char *s) {
  while (*s) uart_putc(*s++);
}
