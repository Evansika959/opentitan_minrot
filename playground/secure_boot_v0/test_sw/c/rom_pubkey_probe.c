// rom_pubkey_probe.c -- diagnostic-only ROM. Isolates exactly one
// question: does the real gates' uECC_compute_public_key, given the real
// PUF-derived private key, produce the SAME public key bytes the host
// packer (and a native x86 re-implementation) computed? No SHA256, no
// verify, no DMEM access, no extra debug prints beyond the one that
// matters -- kept as close in shape/size to the ORIGINAL working full-
// chain build as possible (that one reached "ROM7: K" cleanly in ~155ms;
// the fuller debug build with 4 extra print blocks mysteriously took 4x+
// longer and never got there -- minimizing this program's footprint
// avoids reproducing whatever caused that).
//
// Reference value to compare the printed pubkey against (from the host
// packer AND an independent native x86 uECC run, both agree):
//   51168cd5386d44213e0f3c0e7a6b302ad2a3ed137a41167febe69fe59b4da23050524475e4517d32
#include <stdint.h>
#include "./utils/uart.h"
#include "./utils/micro-ecc/uECC.h"

#define SB7_PUF_BASE 0x00040000u

static inline uint32_t reg_read(uint32_t addr)  { return *(volatile uint32_t *)addr; }
static inline void     reg_write(uint32_t addr, uint32_t val) { *(volatile uint32_t *)addr = val; }

static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }
static void uart_put_hex8(uint8_t v) {
  static const char hexd[] = "0123456789ABCDEF";
  uart_putc(hexd[(v >> 4) & 0xF]);
  uart_putc(hexd[v & 0xF]);
}
static void uart_put_bytes(const uint8_t *buf, unsigned len) {
  for (unsigned i = 0; i < len; ++i) uart_put_hex8(buf[i]);
}

static uint32_t rng_state;
static uint32_t xorshift32(void) {
  uint32_t x = rng_state;
  x ^= x << 13; x ^= x >> 17; x ^= x << 5;
  rng_state = x;
  return x;
}
static int uecc_rng(uint8_t *dest, unsigned size) {
  for (unsigned i = 0; i < size; ++i) dest[i] = (uint8_t)(xorshift32() & 0xFF);
  return 1;
}
static void read_puf_key(uint8_t key[32]) {
  reg_write(SB7_PUF_BASE, 1);
  while (!(reg_read(SB7_PUF_BASE) & 1)) { }
  for (int w = 0; w < 8; w++) {
    uint32_t word = reg_read(SB7_PUF_BASE + 4u + 4u * (uint32_t)w);
    key[w * 4 + 0] = (uint8_t)(word >> 0);
    key[w * 4 + 1] = (uint8_t)(word >> 8);
    key[w * 4 + 2] = (uint8_t)(word >> 16);
    key[w * 4 + 3] = (uint8_t)(word >> 24);
  }
}

int main(void) {
  rng_state = 0x1u;
  uart_puts("PKPROBE: alive\r\n");

  uint8_t puf_key[32];
  read_puf_key(puf_key);
  uart_puts("PKPROBE: puf ");
  uart_put_bytes(puf_key, 32);
  uart_puts("\r\n");

  uECC_set_rng(&uecc_rng);
  const struct uECC_Curve_t *curve = uECC_secp160r1();

  uint8_t private_key[21];
  uint8_t public_key[40];
  int found = 0;
  int found_top = -1;
  for (int i = 0; i < 21; i++) private_key[i] = 0;
  for (int i = 0; i < 20; i++) private_key[i + 1] = puf_key[i];
  for (int top = 0; top <= 1 && !found; top++) {
    private_key[0] = (uint8_t)top;
    if (uECC_compute_public_key(private_key, public_key, curve)) { found = 1; found_top = top; }
  }
  if (!found) {
    uart_puts("PKPROBE: NO KEY!\r\n");
  } else {
    uart_puts("PKPROBE: top=");
    uart_putc((char)('0' + found_top));
    uart_puts(" pubkey ");
    uart_put_bytes(public_key, 40);
    uart_puts("!\r\n");
  }

  while (1) { __asm__ volatile("wfi"); }
  return 0;
}
