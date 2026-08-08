// host_pack_7bank_image.c -- host-side (native gcc) signing/packing tool
// for the top_pd_7bank real secure-boot + PUF demo. Forked from
// host_pack_puf_image.c, with the one change that matters: this includes
// secure_boot_7bank_layout.h -- the SAME header rom_secure_boot_7bank.c
// includes -- for BOOT_IMG_BASE/EXEC_BASE, instead of each file hardcoding
// its own copy of the constant. That divergence (rom_puf_secure_boot.c's
// ROM expected the image at DATA_SRAM_BASE+0x100, while host_pack_puf_
// image.c actually wrote it at DATA_SRAM_BASE+0x260) is a real bug found
// in the earlier top_pd_puf attempt; sharing one header makes that class
// of bug impossible here.
//
// Also: no RESERVED_WORDS/trimming dance -- top_pd_7bank's DMEM is a full
// 1792-word (7KiB) macro, and the ROM's own .rodata/.data/.bss/.stack all
// live in IMEM (see link_7bank_rom.ld), so DMEM is 100% free for the
// packed image starting at word 0.
//
// Signs with uECC/secp160r1, deriving the private key from the same known
// PUF bytes (puf_sim/mc_test/puf_realdata.hex) rom_secure_boot_7bank.c
// will re-derive on-target via the real PUF hardware path.
//
// Usage: host_pack_7bank_image <payload.bin> <out_dmem.hex>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "uECC.h"
#include "sha256.h"
#include "boot_hdr.h"
#include "secure_boot_7bank_layout_spike.h"

#define DMEM_TOTAL_WORDS (SB7_DMEM_SIZE / 4u) // 1792 words

// Same known SPICE-derived PUF bytes rom_secure_boot_7bank.c will re-derive
// on-target (puf_sim/mc_test/puf_realdata.hex).
static const uint8_t puf_key[32] = {
  0x23,0xD9,0xC2,0x92,0x51,0x3E,0x76,0x32,
  0x7C,0x0E,0x65,0x36,0x10,0x14,0x20,0x91,
  0x94,0x13,0x50,0x07,0x01,0x78,0x02,0x82,
  0x0E,0x51,0x81,0x88,0xC4,0x44,0x35,0x0A,
};

static uint32_t rng_state = 1;
static uint32_t xorshift32(void) {
  uint32_t x = rng_state;
  x ^= x << 13; x ^= x >> 17; x ^= x << 5;
  rng_state = x;
  return x;
}
static int host_rng(uint8_t *dest, unsigned size) {
  for (unsigned i = 0; i < size; ++i) dest[i] = (uint8_t)(xorshift32() & 0xFF);
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s <payload.bin> <out_dmem.hex>\n", argv[0]);
    return 1;
  }

  FILE *pf = fopen(argv[1], "rb");
  if (!pf) { perror("fopen payload.bin"); return 1; }
  uint8_t payload[2048];
  size_t payload_len = fread(payload, 1, sizeof(payload), pf);
  fclose(pf);
  if (payload_len == 0) { fprintf(stderr, "payload.bin is empty\n"); return 1; }
  printf("payload: %zu bytes\n", payload_len);

  boot_hdr_t h;
  memset(&h, 0, sizeof(h));
  h.magic       = BOOT_MAGIC;
  h.hdr_version = HDR_VERSION;
  h.hdr_len     = sizeof(boot_hdr_t);
  h.img_type    = IMG_TYPE_BL0;
  h.payload_off = sizeof(boot_hdr_t);
  h.payload_len = (uint32_t)payload_len;
  h.load_addr   = SB7_EXEC_BASE;
  h.entry_addr  = SB7_EXEC_BASE;
  h.sig_off     = (h.payload_off + h.payload_len + 3u) & ~3u;
  h.sig_len     = 40; // secp160r1: r||s, 20 bytes each

  hdr_bind_t bind = {
    .img_type    = h.img_type,
    .payload_len = h.payload_len,
    .load_addr   = h.load_addr,
    .entry_addr  = h.entry_addr,
  };
  uint8_t digest[32];
  sha256_ctx_t sha;
  sha256_init(&sha);
  sha256_update(&sha, (const uint8_t *)&bind, sizeof(bind));
  sha256_update(&sha, payload, payload_len);
  sha256_final(&sha, digest);
  printf("image digest: ");
  for (int i = 0; i < 32; i++) printf("%02x", digest[i]);
  printf("\n");

  uECC_set_rng(&host_rng);
  const struct uECC_Curve_t *curve = uECC_secp160r1();

  uint8_t private_key[21] = {0};
  uint8_t public_key[40]  = {0};
  int found = 0;
  memcpy(private_key + 1, puf_key, 20);
  for (int top = 0; top <= 1 && !found; top++) {
    private_key[0] = (uint8_t)top;
    if (uECC_compute_public_key(private_key, public_key, curve)) found = 1;
  }
  if (!found) { fprintf(stderr, "failed to derive a valid PUF private key\n"); return 1; }
  printf("derived public key: ");
  for (int i = 0; i < 40; i++) printf("%02x", public_key[i]);
  printf("\n");

  uint8_t sig[40];
  if (!uECC_sign(private_key, digest, sizeof(digest), sig, curve)) {
    fprintf(stderr, "uECC_sign failed\n");
    return 1;
  }
  printf("signature: ");
  for (int i = 0; i < 40; i++) printf("%02x", sig[i]);
  printf("\n");

  uint32_t img_total = h.sig_off + h.sig_len;
  uint8_t *img = calloc(1, img_total);
  if (!img) { fprintf(stderr, "oom\n"); return 1; }
  memcpy(img, &h, sizeof(h));
  memcpy(img + h.payload_off, payload, payload_len);
  memcpy(img + h.sig_off, sig, h.sig_len);

  if (img_total > DMEM_TOTAL_WORDS * 4u) {
    fprintf(stderr, "error: packed image (%u bytes) overflows DMEM's %u-word capacity\n",
            img_total, DMEM_TOTAL_WORDS);
    return 1;
  }

  FILE *out = fopen(argv[2], "w");
  if (!out) { perror("fopen out_dmem.hex"); return 1; }
  for (uint32_t w = 0; w < DMEM_TOTAL_WORDS; w++) {
    uint32_t word = 0;
    uint32_t img_byte = w * 4u;
    if (img_byte < img_total) {
      word = (uint32_t)img[img_byte]
           | ((uint32_t)img[img_byte + 1] << 8)
           | ((uint32_t)img[img_byte + 2] << 16)
           | ((uint32_t)img[img_byte + 3] << 24);
    }
    fprintf(out, "%08x\n", word);
  }
  fclose(out);
  free(img);

  printf("wrote %s (%u words, image at word 0, %u bytes)\n", argv[2], DMEM_TOTAL_WORDS, img_total);
  return 0;
}
