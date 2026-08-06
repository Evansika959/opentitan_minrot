// timing_probe.c -- NOT part of the demo. Standalone cycle-count
// measurement for uECC_compute_public_key on rv32im, run under spike
// (fast ISA simulator) instead of burning GLS wall-clock time guessing at
// timeouts. No UART/PUF touched -- just rdcycle before/after the call,
// with the delta left in register a0 and t0 for a spike -d script to read
// via an infinite loop landing point.
#include <stdint.h>
#include "./utils/micro-ecc/uECC.h"

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

static inline uint32_t rdcycle(void) {
  uint32_t c;
  __asm__ volatile("rdcycle %0" : "=r"(c));
  return c;
}

volatile uint32_t g_cycles_before, g_cycles_after, g_delta;
volatile int g_found;

int main(void) {
  rng_state = 0x1u;
  uECC_set_rng(&uecc_rng);
  const struct uECC_Curve_t *curve = uECC_secp160r1();

  uint8_t private_key[21] = {
    0x00,0x23,0xD9,0xC2,0x92,0x51,0x3E,0x76,0x32,0x7C,0x0E,
    0x65,0x36,0x10,0x14,0x20,0x91,0x94,0x13,0x50,0x07
  };
  uint8_t public_key[40];

  g_cycles_before = rdcycle();
  g_found = uECC_compute_public_key(private_key, public_key, curve);
  g_cycles_after = rdcycle();
  g_delta = g_cycles_after - g_cycles_before;

  __asm__ volatile("mv t0, %0" :: "r"(g_delta));
  __asm__ volatile("mv a0, %0" :: "r"(g_delta));

  // volatile asm inside the loop body -- without a side effect here, GCC is
  // entitled (C11 6.8.5p6) to assume this loop terminates and elide it
  // entirely, which is exactly what happened on the first attempt (the
  // disassembly just ended after the mv instructions above, no self-loop
  // to break on at all).
  while (1) { __asm__ volatile(""); }
  return 0;
}
