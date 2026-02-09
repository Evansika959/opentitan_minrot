#include <stdint.h>

#define UART_BASE      0x00030000u
#define UART_CTRL_OFF  0x10u
#define UART_STATUS_OFF 0x14u
#define UART_WDATA_OFF 0x1cu

#define UART_STATUS_TXFULL_MASK 0x1u

#include "./utils/uart.h"

int main(void) {
  uart_putc('A');
  uart_put_hex8(0x7Au);
  uart_put_hex32(0xDEADBEEFu);
  uart_puts("Hello, UART!");
}