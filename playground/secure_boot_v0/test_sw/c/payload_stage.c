// payload_stage.c -- new file.
//
// The verified payload for the "reuse real secure_boot_v0 structure" demo.
// Same role as stage2_demo.c, but this time ROM actually copies these bytes
// from DMEM into ESRAM at runtime (copy_payload(), reused from the real
// rom.c) instead of the payload already sitting pre-baked in the same IMEM
// ROM executes from. No rodata/data (see link_payload.ld) so the signed
// region is pure code.
#include "./utils/uart.h"

void payload_main(void) {
  uart_putc('P');
  uart_putc('a');
  uart_putc('y');
  uart_putc('l');
  uart_putc('o');
  uart_putc('a');
  uart_putc('d');
  uart_putc(':');
  uart_putc(' ');
  uart_putc('v');
  uart_putc('e');
  uart_putc('r');
  uart_putc('i');
  uart_putc('f');
  uart_putc('i');
  uart_putc('e');
  uart_putc('d');
  uart_putc(' ');
  uart_putc('b');
  uart_putc('o');
  uart_putc('o');
  uart_putc('t');
  uart_putc(' ');
  uart_putc('O');
  uart_putc('K');
  uart_putc('\r');
  uart_putc('\n');
  while (1) { }
}
