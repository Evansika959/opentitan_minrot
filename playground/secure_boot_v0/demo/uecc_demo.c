#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "utils/micro-ecc/uECC.h"

static int RNG(uint8_t *dest, unsigned size) {
  FILE *f = fopen("/dev/urandom", "rb");
  if (!f) return 0;
  size_t n = fread(dest, 1, size, f);
  fclose(f);
  return n == size;
}

static int read_key_from_file(const char *path, uint8_t *out, size_t len) {
  FILE *f = fopen(path, "rb");
  if (!f) { perror("fopen"); return 0; }
  size_t n = fread(out, 1, len, f);
  fclose(f);
  return n == len;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <path to 32-byte PUF-derived key>\n", argv[0]);
    return 1;
  }

  uECC_set_rng(&RNG);
  const struct uECC_Curve_t *curve = uECC_secp160r1();

  int priv_size = uECC_curve_private_key_size(curve);  // 21

  uint8_t puf_key[32];
  if (!read_key_from_file(argv[1], puf_key, sizeof(puf_key))) {
    fprintf(stderr, "Failed to read PUF-derived key from %s\n", argv[1]);
    return 1;
  }

  uint8_t private_key[21] = {0};
  uint8_t public_key[40]  = {0};
  int found = 0;

  // secp160r1's order n needs ~161 bits, not the full 168 (21 bytes).
  // Copy the first 20 bytes as the bulk of the scalar, but only try
  // small values (0 or 1) for the top byte, since anything larger
  // almost certainly exceeds the curve order.
  memcpy(private_key + 1, puf_key, 20);

  for (int top = 0; top <= 1 && !found; top++) {
    private_key[0] = (uint8_t)top;
    if (uECC_compute_public_key(private_key, public_key, curve)) {
      found = 1;
      printf("Valid private key found with top byte = %d\n", top);
    }
  }

  if (!found) {
    fprintf(stderr, "uECC_compute_public_key failed for both top-byte candidates\n");
    return 1;
  }

  static const uint8_t msg[32] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
    0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
    0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,
  };

  uint8_t sig[40];
  if (!uECC_sign(private_key, msg, sizeof(msg), sig, curve)) {
    fprintf(stderr, "uECC_sign failed\n");
    return 1;
  }

  printf("PUF-derived private key (%d bytes): ", priv_size);
  for (int i = 0; i < priv_size; i++) printf("%02x", private_key[i]);
  printf("\n");

  int ok = uECC_verify(public_key, msg, sizeof(msg), sig, curve);
  printf("verify: %s\n", ok ? "OK" : "FAIL");
  return ok ? 0 : 1;
}
