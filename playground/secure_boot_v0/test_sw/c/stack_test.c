#include <stdint.h>

#define DMEM_BASE   0x00020000u
#define STATUS_ADDR (DMEM_BASE + 0x80)
#define PASS 0x1u
#define FAIL 0xDEAD0000u

#define UART_BASE              0x00030000u
#define UART_CTRL_OFF          0x10
#define UART_STATUS_OFF        0x14
#define UART_WDATA_OFF         0x1C
#define UART_STATUS_TXFULL_MASK 0x1u

static inline uint32_t read_sp(void) {
  uint32_t sp;
  asm volatile ("mv %0, sp" : "=r"(sp));
  return sp;
}

static uint32_t probe_depth(uint32_t depth) {
  volatile uint32_t locals[4] = {0};
  locals[0] = depth;
  return locals[0] + (depth ? probe_depth(depth - 1) : 0);
}

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

static void uart_print_str(const char *s) {
  while (*s) {
    uart_putc(*s++);
  }
}

static void uart_print_hex32(uint32_t v) {
  for (int i = 7; i >= 0; --i) {
    uint8_t nib = (v >> (i * 4)) & 0xF;
    uart_putc(nib < 10 ? ('0' + nib) : ('a' + (nib - 10)));
  }
}

int main(void) {
  volatile uint32_t *status = (uint32_t *)STATUS_ADDR;

  uint32_t sp0 = read_sp();
  uint32_t sp1 = probe_depth(3); // exercise stack push/pop
  uint32_t sp2 = read_sp();

  // Simple sanity: SP should not increase; allow some slack for alignment.
  if (sp2 <= sp0 && sp1 == 3 + 2 + 1 + 0) {
    *status = PASS;
    uart_print_str("PASS sp0=");
  } else {
    *status = FAIL;
    uart_print_str("FAIL sp0=");
  }

  uart_print_hex32(sp0);
  uart_print_str(" sp2=");
  uart_print_hex32(sp2);
  uart_print_str(" sum=");
  uart_print_hex32(sp1);
  uart_print_str("\n");

  // Idle forever
  while (1) { asm volatile ("wfi"); }
}