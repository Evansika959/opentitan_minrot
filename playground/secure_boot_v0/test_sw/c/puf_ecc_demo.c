// puf_ecc_demo.c
//
// New file (does not modify anything existing in test_sw/) -- derives an
// ECC key from the SRAM PUF's response, computes the public key, signs a
// fixed test message, and verifies it. Matches demo/uecc_demo.c's
// top-byte-search approach for turning 32 PUF-derived bytes into a valid
// secp160r1 scalar, just running on Ibex instead of a host machine.
//
// Built through secure_boot_v0/test_sw's existing, proven infrastructure
// unchanged: crt0.S (stack + BSS init), link.ld (IMEM @ 0x0 / DMEM @
// 0x20000), uart.c/uart.h (real TL-UL uart driver), mem.c/memset.c/compat.c
// (freestanding memcpy/memset/__lshrdi3 shims), uECC.c (the crypto library
// itself). Targets puf_ibex_tlul_top (the plain-TL-UL variant with
// large-capacity IMEM/DMEM) -- micro-ecc measures ~18-24KB compiled, far
// beyond the 1 KiB OCD-cell macro's capacity, so this deliberately isn't
// the OCD-macro variant.
#include <stdint.h>
#include "./utils/uart.h"
#include "./utils/micro-ecc/uECC.h"

#define PUF_BASE 0x10000u

static inline void reg_write(uint32_t addr, uint32_t val) {
  *(volatile uint32_t *)addr = val;
}
static inline uint32_t reg_read(uint32_t addr) {
  return *(volatile uint32_t *)addr;
}

static void uart_puts(const char *s) {
  while (*s) uart_putc(*s++);
}

static void uart_put_hex8(uint8_t v) {
  static const char hexd[] = "0123456789ABCDEF";
  uart_putc(hexd[(v >> 4) & 0xF]);
  uart_putc(hexd[v & 0xF]);
}

static void uart_put_bytes(const uint8_t *buf, unsigned len) {
  for (unsigned i = 0; i < len; ++i) uart_put_hex8(buf[i]);
}

// Deterministic RNG for micro-ecc's signing nonce (fine for a demo/self-test
// -- same approach as test_sw/c/uecc_test_64.c's self-test RNG).
static uint32_t rng_state;

static uint32_t xorshift32(void) {
  uint32_t x = rng_state;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  rng_state = x;
  return x;
}

static int uecc_rng(uint8_t *dest, unsigned size) {
  for (unsigned i = 0; i < size; ++i) dest[i] = (uint8_t)(xorshift32() & 0xFF);
  return 1;
}

// Trigger a PUF sample, poll for done, and pull the first 32 of the 64
// response bytes (matches the regif's CTRL @ +0x0, DATA0.. @ +0x4 layout).
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

  uart_puts("PUF-ECC demo starting\r\n");

  uint8_t puf_key[32];
  read_puf_key(puf_key);
  uart_puts("PUF key:     ");
  uart_put_bytes(puf_key, 32);
  uart_puts("\r\n");

  uECC_set_rng(&uecc_rng);
  const struct uECC_Curve_t *curve = uECC_secp160r1();

  uint8_t private_key[21];
  uint8_t public_key[40];
  int found = 0;

  for (int i = 0; i < 21; i++) private_key[i] = 0;
  for (int i = 0; i < 20; i++) private_key[i + 1] = puf_key[i];

  // secp160r1's order n needs ~161 bits, not the full 168 (21 bytes).
  // Only try small top-byte candidates, since anything larger almost
  // certainly exceeds the curve order (same approach as demo/uecc_demo.c).
  for (int top = 0; top <= 1 && !found; top++) {
    private_key[0] = (uint8_t)top;
    if (uECC_compute_public_key(private_key, public_key, curve)) {
      found = 1;
    }
  }

  if (!found) {
    uart_puts("FAIL: no valid private key\r\n");
    while (1) { }
  }

  uart_puts("Private key: ");
  uart_put_bytes(private_key, 21);
  uart_puts("\r\n");
  uart_puts("Public key:  ");
  uart_put_bytes(public_key, 40);
  uart_puts("\r\n");

  static const uint8_t msg[32] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
    0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
    0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
  };

  uint8_t sig[40];
  if (!uECC_sign(private_key, msg, sizeof(msg), sig, curve)) {
    uart_puts("FAIL: sign\r\n");
    while (1) { }
  }
  uart_puts("Signature:   ");
  uart_put_bytes(sig, 40);
  uart_puts("\r\n");

  int ok = uECC_verify(public_key, msg, sizeof(msg), sig, curve);
  uart_puts(ok ? "VERIFY OK\r\n" : "VERIFY FAIL\r\n");

  while (1) { }
  return 0;
}
