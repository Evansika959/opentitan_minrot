#ifndef SW_UTILS_UART_SPIKE_H_
#define SW_UTILS_UART_SPIKE_H_
// uart_spike.h -- spike-only copy of test_sw/c/utils/uart.h, UART_BASE
// shifted to match secure_boot_7bank_layout_spike.h's address map. See
// that header for why the shift exists.
#include <stdint.h>

#define UART_BASE               0x80030000u
#define UART_CTRL_OFF           0x10u
#define UART_STATUS_OFF         0x14u
#define UART_WDATA_OFF          0x1Cu
#define UART_STATUS_TXFULL_MASK 0x1u

void uart_putc(char c);

#endif
