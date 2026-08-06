// rom_7bank_stageA.c -- validation-only ROM for top_pd_7bank.
//
// This deliberately does NOT touch DMEM or verify anything yet. It exists
// to isolate and prove, on the real taped-out netlist, the one thing that
// has never actually been exercised there before: compiled C (crt0 stack
// setup, static-data, function calls) plus the uECC/SHA256 library, as
// opposed to the hand-written assembly every previous top_pd_7bank GLS test
// used. The earlier top_pd_puf attempt at this same idea (rom_puf_secure_
// boot.c) burned ~49 hours of GLS wall-clock time and produced zero UART
// bytes -- i.e. it never even got past this stage -- so this is checked in
// isolation first before adding DMEM verify+copy+jump on top of it.
//
// Sequence: UART hello -> derive PUF-based key (real PUF trigger/poll/read,
// same register interface gls/smoke_puf_boot.S already proved works) ->
// compute a real secp160r1 public key from it (uECC) -> print both -> halt.
#include <stdint.h>
#include "./utils/uart.h"
#include "./utils/micro-ecc/uECC.h"

static inline uint32_t reg_read(uint32_t addr)  { return *(volatile uint32_t *)addr; }
static inline void reg_write(uint32_t addr, uint32_t val) { *(volatile uint32_t *)addr = val; }

#define PUF_BASE 0x00040000u

static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }

static void uart_put_hex8(uint8_t v) {
  static const char hexd[] = "0123456789ABCDEF";
  uart_putc(hexd[(v >> 4) & 0xF]);
  uart_putc(hexd[v & 0xF]);
}
static void uart_put_bytes(const uint8_t *buf, unsigned len) {
  for (unsigned i = 0; i < len; ++i) uart_put_hex8(buf[i]);
}

// ====== deterministic RNG for uECC (no real entropy source needed for this
// demo -- uECC just needs *a* RNG to exist for point ops / key derivation) ======
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
  uart_puts("ROM7: puf_key ");
  uart_put_bytes(puf_key, 32);
  uart_puts("\r\n");

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
    uart_puts("ROM7: KEYDERIVE FAIL\r\n");
  } else {
    uart_puts("ROM7: pubkey ");
    uart_put_bytes(public_key, 40);
    uart_puts("\r\n");
  }

  uart_puts("ROM7: DONE!\r\n");
  while (1) { __asm__ volatile("wfi"); }
  return 0;
}
