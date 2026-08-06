// payload_stage_7bank_spike.c -- spike-only copy of payload_stage_7bank.c,
// pointed at uart_spike.h. Logic identical; only UART_BASE differs.
#include "uart_spike.h"

void payload_main(void) {
  const char *msg = "Payload: verified boot OK!\r\n";
  while (*msg) uart_putc(*msg++);
  while (1) { __asm__ volatile(""); }
}
