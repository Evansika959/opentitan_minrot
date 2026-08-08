// modmult_bench.c -- isolates uECC_vli_modMult_fast (secp160r1) with a
// small FIXED call count, printing a marker after each call. Used to A/B
// test whether uECC_OPTIMIZATION_LEVEL's default (2, curve->mmod_fast /
// omega_mult_secp160r1) hangs versus level 0 (generic uECC_vli_mmod).
#include <stdint.h>
#include "./utils/uart.h"
#include "./utils/micro-ecc/uECC.h"
#include "./utils/micro-ecc/uECC_vli.h"

static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }
static void uart_put_hex8(uint8_t v) {
  static const char hexd[] = "0123456789ABCDEF";
  uart_putc(hexd[(v >> 4) & 0xF]);
  uart_putc(hexd[v & 0xF]);
}
static void uart_put_bytes(const uint8_t *buf, unsigned len) {
  for (unsigned i = 0; i < len; ++i) uart_put_hex8(buf[i]);
}

#define NUM_CALLS 8
#define MY_MAX_WORDS 8  /* comfortably >= secp160r1's real 5 words @ 32-bit */

// Real, non-degenerate 20-byte values (not the actual curve prime/generator
// -- just large, "full" magnitude operands so the reduction path sees
// realistic-sized products, same order of magnitude as any real point-mult
// intermediate).
static const uint8_t LEFT_BYTES[20] = {
  0xA4,0x3B,0x91,0xF0,0x2C,0x77,0xE8,0x15,0x6D,0x9A,
  0x3F,0x88,0x21,0xC4,0x5E,0xB0,0x77,0x62,0xD9,0x0F,
};
static const uint8_t RIGHT_BYTES[20] = {
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

int main(void) {
  uart_puts("BENCH: alive\r\n");

  const struct uECC_Curve_t *curve = uECC_secp160r1();

  uECC_word_t left[MY_MAX_WORDS];
  uECC_word_t right[MY_MAX_WORDS];
  uECC_word_t result[MY_MAX_WORDS];
  for (int i = 0; i < MY_MAX_WORDS; i++) { left[i] = 0; right[i] = 0; result[i] = 0; }
  uECC_vli_bytesToNative(left, LEFT_BYTES, 20);
  uECC_vli_bytesToNative(right, RIGHT_BYTES, 20);

  for (int call = 0; call < NUM_CALLS; call++) {
    uart_puts("BENCH: call ");
    uart_putc((char)('0' + call));
    uart_puts(" start\r\n");

    uECC_vli_modMult_fast(result, left, right, curve);

    uart_puts("BENCH: call ");
    uart_putc((char)('0' + call));
    uart_puts(" done result=");
    {
      uint8_t out[20];
      uECC_vli_nativeToBytes(out, 20, result);
      uart_put_bytes(out, 20);
    }
    uart_puts("\r\n");

    // feed result back in so successive calls see varied operands
    for (int i = 0; i < MY_MAX_WORDS; i++) { left[i] = result[i]; }
  }

  uart_puts("BENCH: ALL DONE\r\n");
  while (1) { __asm__ volatile("wfi"); }
  return 0;
}
