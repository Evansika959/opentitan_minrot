// rom_7bank_stageA_spike.c -- spike-address-shifted copy of
// rom_7bank_stageA.c (crt0 + real PUF-derive-key + real secp160r1
// compute_public_key, no DMEM/verify/copy/jump). Same purpose as the
// other _spike variants: address-shifted to 0x80000000 to avoid spike's
// own boot-trampoline device at [0, 0x1000), used as the golden reference
// for a checkpoint comparison against the real GLS gates running the
// unmodified, real-address rom_7bank_stageA.c binary.
#include <stdint.h>
#include "uart_spike.h"
#include "uECC.h"

static inline uint32_t reg_read(uint32_t addr)  { return *(volatile uint32_t *)addr; }
static inline void reg_write(uint32_t addr, uint32_t val) { *(volatile uint32_t *)addr = val; }

#define PUF_BASE 0x80040000u

static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }

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
  reg_write(PUF_BASE, 1);
  while (!(reg_read(PUF_BASE) & 1)) { }
  for (int w = 0; w < 8; w++) {
    uint32_t word = reg_read(PUF_BASE + 4u + 4u * (uint32_t)w);
    key[w * 4 + 0] = (uint8_t)(word >> 0);
    key[w * 4 + 1] = (uint8_t)(word >> 8);
    key[w * 4 + 2] = (uint8_t)(word >> 16);
    key[w * 4 + 3] = (uint8_t)(word >> 24);
  }
}

int main(void) {
  rng_state = 0x1u;
  uart_puts("ROM7: alive\r\n");

  uint8_t puf_key[32];
  read_puf_key(puf_key);
  uart_puts("ROM7: P\r\n");

  uECC_set_rng(&uecc_rng);
  const struct uECC_Curve_t *curve = uECC_secp160r1();

  uint8_t private_key[21];
  uint8_t public_key[40];
  int found = 0;
  for (int i = 0; i < 21; i++) private_key[i] = 0;
  for (int i = 0; i < 20; i++) private_key[i + 1] = puf_key[i];
  for (int top = 0; top <= 1 && !found; top++) {
    private_key[0] = (uint8_t)top;
    if (uECC_compute_public_key(private_key, public_key, curve)) found = 1;
  }

  if (!found) {
    uart_puts("ROM7: KEYDERIVE FAIL!\r\n");
  } else {
    uart_puts("ROM7: K\r\n");
  }

  uart_puts("ROM7: DONE!\r\n");
  while (1) { __asm__ volatile(""); }
  return 0;
}
