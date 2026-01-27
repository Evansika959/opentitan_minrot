// bl0.c
#include <stdint.h>

// UART stubs (replace with your known-good)
static inline void uart_putc(char c) { (void)c; }
static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }

int main(void) {
  uart_puts("BL0\n");
  while (1) { __asm__ volatile("wfi"); }
}
