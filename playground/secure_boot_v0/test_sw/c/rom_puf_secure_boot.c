// rom_puf_secure_boot.c -- new file.
//
// ROM stage for the "reuse real secure_boot_v0 structure" demo. Almost all
// of verify_header()/compute_digest()/copy_payload()/jump_to()/
// add_overflow_u32()/in_range_len() are reused verbatim from the real
// test_sw/c/rom.c (same bounds checks, same hdr_bind_t-based digest binding
// signature to length+addresses -- closing the "fixed hash window" gap the
// earlier from-scratch rom_secure_boot_demo.c had). Two real differences
// from rom.c:
//   1. secp160r1 instead of secp256r1 (sig_len 40, not 64) -- kept per
//      explicit request rather than switching curves.
//   2. The public key is derived from the PUF at boot instead of loaded
//      from a hardcoded ./utils/trusted_pubkey.h -- so verification is
//      actually ENABLED here (real rom.c currently ships with its
//      verify_header()/uECC_verify() call commented out).
//
// boot_hdr.h (64-byte boot_hdr_t / 16-byte hdr_bind_t) is the real,
// unmodified header already present in this directory.
#include <stdint.h>
#include <stdbool.h>
#include "boot_hdr.h"
#include "./utils/uart.h"
#include "./utils/sha256.h"
#include "./utils/micro-ecc/uECC.h"

// Real secure_boot_v0 address-map constants (EXEC_BASE / DATA_SRAM_BASE /
// BOOT_IMG_BASE match sw/boot/rom.c and sw/tools/pack_image.py's naming
// convention, but the SIZEs below were corrected for top_pd_puf specifically
// -- top_pd_puf.sv's u_esram/u_dmem are both the real, physically-taped-out
// tlul_sram_if_macro (MacroAw=8 in tlul_sram_if_macro.sv -- 256 words = 1KiB,
// hard-fixed by the macro, not a parameter). The ORIGINAL constants here
// (16KB/4KB) matched the macro21 demo's IDEALIZED memories, which have no
// real capacity limit -- reusing them against the real macro would let
// verify_header()'s own in_range_len() bounds checks pass for addresses that
// don't physically exist (the macro wraps/aliases anything past word 256
// back onto the same 256 words), silently corrupting data instead of
// catching the problem. BOOT_IMG_BASE's reserve was cut from 0x1000 (1024
// words, matching replace_dmem.py's generic convention) to 0x100 (64 words)
// -- see run_top_pd_puf_demo.bash for how this is verified against the
// ROM's actual compiled .dmem footprint before packing.
#define DATA_SRAM_BASE   0x00020000u
#define DATA_SRAM_SIZE   0x00000400u   // 1KiB (u_dmem, real tlul_sram_if_macro)
#define EXEC_BASE        0x00010000u
#define EXEC_SIZE        0x00000400u   // 1KiB (u_esram, real tlul_sram_if_macro)
#define BOOT_IMG_BASE    0x00020100u   // DATA_SRAM_BASE + 0x100 (64 words reserved)
#define PUF_BASE         0x00040000u

typedef void (*entry_fn_t)(void);

static void uart_puts(const char *s);
static void die(const char *msg);
static bool add_overflow_u32(uint32_t a, uint32_t b, uint32_t *out);
static bool in_range_len(uint32_t addr, uint32_t len, uint32_t base, uint32_t size);
static void compute_digest(const boot_hdr_t *h, const uint8_t *payload, uint8_t digest[32]);
static void verify_header(const boot_hdr_t *h, uint32_t img_base, uint32_t expected_type);
static void copy_payload(uint32_t dst_addr, const uint8_t *src, uint32_t len);
static void jump_to(uint32_t entry_addr);
static void uart_put_hex8(uint8_t v);
static void uart_put_bytes(const uint8_t *buf, unsigned len);

static inline uint32_t reg_read(uint32_t addr) { return *(volatile uint32_t *)addr; }
static inline void     reg_write(uint32_t addr, uint32_t val) { *(volatile uint32_t *)addr = val; }

// ====== PUF-derived key (replaces trusted_pubkey.h) ======
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

static uint8_t g_pubkey[40];

int main(void) {
  rng_state = 0x1u;

  uart_puts("ROM: deriving PUF key\r\n");
  uint8_t puf_key[32];
  read_puf_key(puf_key);

  uECC_set_rng(&uecc_rng);
  const struct uECC_Curve_t *curve = uECC_secp160r1();

  uint8_t private_key[21];
  int found = 0;
  for (int i = 0; i < 21; i++) private_key[i] = 0;
  for (int i = 0; i < 20; i++) private_key[i + 1] = puf_key[i];
  for (int top = 0; top <= 1 && !found; top++) {
    private_key[0] = (uint8_t)top;
    if (uECC_compute_public_key(private_key, g_pubkey, curve)) found = 1;
  }
  if (!found) die("ROM: NO KEY");
  uart_puts("ROM: pubkey ");
  uart_put_bytes(g_pubkey, 40);
  uart_puts("\r\n");

  const uint32_t img_base = BOOT_IMG_BASE;
  const boot_hdr_t *h = (const boot_hdr_t *)(uintptr_t)img_base;

  verify_header(h, img_base, IMG_TYPE_BL0);

  const uint8_t *payload = (const uint8_t *)(uintptr_t)(img_base + h->payload_off);
  const uint8_t *sig     = (const uint8_t *)(uintptr_t)(img_base + h->sig_off);

  uint8_t digest[32];
  compute_digest(h, payload, digest);
  uart_puts("ROM: digest ");
  uart_put_bytes(digest, 32);
  uart_puts("\r\n");

  if (!uECC_verify(g_pubkey, digest, 32, sig, curve)) {
    die("ROM: VERIFY FAIL");
  }
  uart_puts("ROM: verify OK\r\n");

  copy_payload(h->load_addr, payload, h->payload_len);
  jump_to(h->entry_addr);

  die("ROM: NO RETURN");
  return 0;
}

// ====== UART ======
static void uart_puts(const char *s) { while (*s) uart_putc(*s++); }

static void die(const char *msg) {
  uart_puts(msg);
  uart_puts("\r\n");
  while (1) { __asm__ volatile("wfi"); }
}

static void uart_put_hex8(uint8_t v) {
  static const char hexd[] = "0123456789ABCDEF";
  uart_putc(hexd[(v >> 4) & 0xF]);
  uart_putc(hexd[v & 0xF]);
}
static void uart_put_bytes(const uint8_t *buf, unsigned len) {
  for (unsigned i = 0; i < len; ++i) uart_put_hex8(buf[i]);
}

// ====== Reused verbatim from the real test_sw/c/rom.c ======
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
  hdr_bind_t bind = {
    .img_type    = h->img_type,
    .payload_len = h->payload_len,
    .load_addr   = h->load_addr,
    .entry_addr  = h->entry_addr,
  };
  sha256_ctx_t ctx;
  sha256_init(&ctx);
  sha256_update(&ctx, (const uint8_t *)&bind, sizeof(bind));
  sha256_update(&ctx, payload, h->payload_len);
  sha256_final(&ctx, digest);
}

// Error strings consolidated to fit the real 1KiB DMEM's byte budget (see
// the address-map comment above) -- every one of the 9 header-field checks
// below shared ONE "ROM: BAD HDR" string and every one of the 5
// range/overlap checks shared ONE "ROM: BAD RANGE" string, instead of a
// distinct ~15-20 byte message each (~187 bytes saved total). This loses
// per-check diagnostic specificity in the UART trace -- acceptable for this
// smoke-level cross-reference test; restore individual messages if actually
// debugging a verification failure and DMEM headroom allows it.
static void verify_header(const boot_hdr_t *h, uint32_t img_base, uint32_t expected_type) {
  if (h->magic != BOOT_MAGIC) die("ROM: BAD HDR");
  if (h->hdr_version != HDR_VERSION) die("ROM: BAD HDR");
  if (h->hdr_len != sizeof(boot_hdr_t)) die("ROM: BAD HDR");
  if (h->img_type != expected_type) die("ROM: BAD HDR");
  if ((h->payload_off & 3u) != 0) die("ROM: BAD HDR");
  if ((h->sig_off & 3u) != 0) die("ROM: BAD HDR");
  if ((h->load_addr & 3u) != 0) die("ROM: BAD HDR");
  if ((h->entry_addr & 3u) != 0) die("ROM: BAD HDR");
  if (h->sig_len != 40u) die("ROM: BAD HDR");   // secp160r1: r||s, 20 bytes each

  uint32_t payload_src = img_base + h->payload_off;
  uint32_t sig_src     = img_base + h->sig_off;

  if (h->payload_off < h->hdr_len) die("ROM: BAD RANGE");
  if (!in_range_len(payload_src, h->payload_len, DATA_SRAM_BASE, DATA_SRAM_SIZE)) die("ROM: BAD RANGE");
  if (!in_range_len(sig_src, h->sig_len, DATA_SRAM_BASE, DATA_SRAM_SIZE)) die("ROM: BAD RANGE");
  if (!in_range_len(h->load_addr, h->payload_len, EXEC_BASE, EXEC_SIZE)) die("ROM: BAD RANGE");
  if (h->entry_addr < h->load_addr || h->entry_addr >= (h->load_addr + h->payload_len)) die("ROM: BAD RANGE");
}

static void copy_payload(uint32_t dst_addr, const uint8_t *src, uint32_t len) {
  volatile uint8_t *dst = (volatile uint8_t *)(uintptr_t)dst_addr;
  for (uint32_t i = 0; i < len; ++i) {
    dst[i] = src[i];
  }
}

static void jump_to(uint32_t entry_addr) {
  ((entry_fn_t)(uintptr_t)entry_addr)();
}
