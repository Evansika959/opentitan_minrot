#ifndef SW_UTILS_UART_H_
#define SW_UTILS_UART_H_

#include <stdint.h>

#define UART_BASE               0x00030000u
#define UART_CTRL_OFF           0x10u
#define UART_STATUS_OFF         0x14u
#define UART_WDATA_OFF          0x1Cu
#define UART_STATUS_TXFULL_MASK 0x1u

void uart_putc(char c);
void uart_puts(const char *s);
void uart_put_hex8(uint8_t v);
void uart_put_hex32(uint32_t v);

#endif // SW_UTILS_UART_H_
