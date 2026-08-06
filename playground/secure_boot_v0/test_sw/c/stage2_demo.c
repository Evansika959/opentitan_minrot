// stage2_demo.c
//
// New file -- the "verified payload" of a minimal 2-stage secure boot demo.
// Not a separate program in the OS sense: ROM (rom_secure_boot_demo.c)
// verifies this function's bytes, then reaches it via a plain function-
// pointer call, not a CPU reset -- so it inherits ROM's already-initialized
// stack and just runs as an ordinary function. No crt0, no rodata (avoided
// deliberately -- see link_stage2.ld -- to keep the signed region to pure
// code, no cross-referenced data section to also merge/place).
//
// Placed at a fixed address (0xF000, see link_stage2.ld) so the bytes ROM
// hashes and verifies are exactly the bytes that end up at the address ROM
// jumps to.
#include "./utils/uart.h"

void stage2_main(void) {
  uart_putc('S');
  uart_putc('t');
  uart_putc('a');
  uart_putc('g');
  uart_putc('e');
  uart_putc('2');
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
