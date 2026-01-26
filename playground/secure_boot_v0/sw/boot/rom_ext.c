// rom_ext.c
#include <stdint.h>
#include <stdbool.h>
#include "boot_hdr.h"
#include "../utils/sha256.h"

#include "../crypto/micro-ecc/uECC.h"
#include "trusted_pubkey.h"

// Same constants as ROM (keep consistent)
#define DATA_SRAM_BASE   0x00020000u
#define DATA_SRAM_SIZE   0x00010000u
#define EXEC_BASE        0x00010000u
#define EXEC_SIZE        0x00010000u
#define BL0_IMG_BASE     0x00023000u

// UART stubs (replace with your known-good)
static inline void uart_putc(char c) { (void)c; }
static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }

static void die(const char *msg) {
  uart_puts(msg); uart_puts("\n");
  while (1) { __asm__ volatile("wfi"); }
}

static bool add_overflow_u32(uint32_t a, uint32_t b, uint32_t *out) {
  uint32_t s = a + b;
  if (s < a) return true;
  *out = s;
  return false;
}
static bool in_range_len(uint32_t addr, uint32_t len, uint32_t base, uint32_t size) {
  if (len == 0) return false;
  uint32_t end;
  if (add_overflow_u32(addr, len, &end)) return false;
  return (addr >= base) && (end <= base + size);
}

static void compute_digest(const boot_hdr_t *h, const uint8_t *payload, uint8_t digest[32]) {
  hdr_bind_t bind = { h->img_type, h->payload_len, h->load_addr, h->entry_addr };
  sha256_ctx_t ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, (const uint8_t *)&bind, sizeof(bind));
  sha256_update(&ctx, payload, h->payload_len);
  sha256_final(&ctx, digest);
}

static void verify_header(const boot_hdr_t *h, uint32_t img_base, uint32_t expected_type) {
  if (h->magic != BOOT_MAGIC) die("ROM_EXT: BAD MAGIC");
  if (h->hdr_version != HDR_VERSION) die("ROM_EXT: BAD HDR VER");
  if (h->hdr_len != sizeof(boot_hdr_t)) die("ROM_EXT: BAD HDR LEN");
  if (h->img_type != expected_type) die("ROM_EXT: BAD IMG TYPE");
  if ((h->payload_off & 3u) != 0) die("ROM_EXT: PAYLOAD ALIGN");
  if ((h->sig_off & 3u) != 0) die("ROM_EXT: SIG ALIGN");
  if ((h->load_addr & 3u) != 0) die("ROM_EXT: LOAD ALIGN");
  if ((h->entry_addr & 3u) != 0) die("ROM_EXT: ENTRY ALIGN");
  if (h->sig_len != 64u) die("ROM_EXT: SIG LEN");

  uint32_t payload_src = img_base + h->payload_off;
  uint32_t sig_src     = img_base + h->sig_off;

  if (h->payload_off < h->hdr_len) die("ROM_EXT: PAYLOAD OVERLAP");
  if (!in_range_len(payload_src, h->payload_len, DATA_SRAM_BASE, DATA_SRAM_SIZE)) die("ROM_EXT: PAYLOAD OOB");
  if (!in_range_len(sig_src, h->sig_len, DATA_SRAM_BASE, DATA_SRAM_SIZE)) die("ROM_EXT: SIG OOB");
  if (!in_range_len(h->load_addr, h->payload_len, EXEC_BASE, EXEC_SIZE)) die("ROM_EXT: LOAD OOB");
  if (h->entry_addr < h->load_addr || h->entry_addr >= (h->load_addr + h->payload_len)) die("ROM_EXT: ENTRY OOB");
}

static void copy_payload(uint32_t dst_addr, const uint8_t *src, uint32_t len) {
  volatile uint8_t *dst = (volatile uint8_t *)(uintptr_t)dst_addr;
  for (uint32_t i=0;i<len;i++) dst[i] = src[i];
  __asm__ volatile("fence.i");
}

typedef void (*entry_fn_t)(void);
static void jump_to(uint32_t entry_addr) { ((entry_fn_t)(uintptr_t)entry_addr)(); }

// Minimal entry
__attribute__((section(".text.start")))
void _start(void) {
  uart_puts("ROM_EXT\n");

  const uint32_t img_base = BL0_IMG_BASE;
  const boot_hdr_t *h = (const boot_hdr_t *)(uintptr_t)img_base;

  verify_header(h, img_base, IMG_TYPE_BL0);

  const uint8_t *payload = (const uint8_t *)(uintptr_t)(img_base + h->payload_off);
  const uint8_t *sig     = (const uint8_t *)(uintptr_t)(img_base + h->sig_off);

  uint8_t digest[32];
  compute_digest(h, payload, digest);

  if (!uECC_verify(TRUSTED_PUBKEY_XY, digest, 32, sig, uECC_secp256r1())) {
    die("ROM_EXT: BL0 FAIL");
  }

  uart_puts("ROM_EXT: BL0 OK\n");
  copy_payload(h->load_addr, payload, h->payload_len);
  jump_to(h->entry_addr);

  die("ROM_EXT: RETURNED");
}
