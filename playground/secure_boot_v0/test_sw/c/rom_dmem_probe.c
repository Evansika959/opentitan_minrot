// rom_dmem_probe.c -- diagnostic-only ROM. No crypto, no PUF, no
// compute-heavy anything: exists purely to answer one question fast --
// does the real DMEM macro read back exactly what the GLS testbench
// backdoor-loaded into it? Reads the packed container's bytes directly
// via plain volatile byte loads (matching how compute_digest's payload
// scan and the boot_hdr_t field reads access DMEM in
// rom_secure_boot_7bank.c) and hex-dumps them over UART. No uECC/sha256
// linked in at all, so total runtime is a few thousand cycles instead of
// the ~1M+ cycles compute_public_key/uECC_verify need -- this should
// complete in seconds of wall-clock, not tens of minutes.
#include <stdint.h>
#include "./utils/uart.h"

#define SB7_DMEM_BASE 0x00020000u
#define PROBE_LEN     256u  // covers header(64) + payload(149) + pad + sig(40), all of it

static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }
static void uart_put_hex8(uint8_t v) {
  static const char hexd[] = "0123456789ABCDEF";
  uart_putc(hexd[(v >> 4) & 0xF]);
  uart_putc(hexd[v & 0xF]);
}

int main(void) {
  uart_puts("PROBE: alive\r\n");

  // Byte-granularity reads -- same access pattern compute_digest's payload
  // scan uses (SHA256 over a uint8_t*), the access pattern most in
  // question here.
  uart_puts("PROBE: BYTES ");
  const volatile uint8_t *b = (const volatile uint8_t *)(uintptr_t)SB7_DMEM_BASE;
  for (unsigned i = 0; i < PROBE_LEN; i++) uart_put_hex8(b[i]);
  uart_puts("\r\n");

  // Word-granularity reads of the same range -- the access pattern
  // boot_hdr_t's uint32_t fields use.
  uart_puts("PROBE: WORDS ");
  const volatile uint32_t *w = (const volatile uint32_t *)(uintptr_t)SB7_DMEM_BASE;
  for (unsigned i = 0; i < PROBE_LEN / 4; i++) {
    uint32_t v = w[i];
    uart_put_hex8((uint8_t)(v >> 0));
    uart_put_hex8((uint8_t)(v >> 8));
    uart_put_hex8((uint8_t)(v >> 16));
    uart_put_hex8((uint8_t)(v >> 24));
  }
  uart_puts("!\r\n");

  while (1) { __asm__ volatile("wfi"); }
  return 0;
}
