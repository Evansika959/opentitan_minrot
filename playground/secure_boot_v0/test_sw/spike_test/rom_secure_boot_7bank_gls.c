// rom_secure_boot_7bank_gls.c -- ROM stage for the real secure-boot + PUF demo
// on top_pd_7bank. Builds on rom_7bank_stageA.c (already validated on the
// real GLS gates: crt0/stack/UART/PUF-derive-key all work) by adding the
// actual secure-boot mechanism: verify a signed BL0 container staged in
// DMEM, using a PUF-derived secp160r1 public key, then copy the verified
// payload to ESRAM and jump to it.
//
// verify_header()/compute_digest()/copy_payload()/jump_to()/
// add_overflow_u32()/in_range_len() follow the real test_sw/c/rom.c's
// structure (same bounds-checked in_range_len logic, same hdr_bind_t-based
// digest binding signature to length+addresses) -- adapted from
// rom_puf_secure_boot.c, which established the PUF-derived-key variant.
//
// Deliberately does NOT reuse rom_puf_secure_boot.c's DATA_SRAM_BASE/
// EXEC_BASE/BOOT_IMG_BASE constants: that file (and its paired host_pack_
// puf_image.c) hardcoded two DIFFERENT BOOT_IMG_BASE values (0x20100 here
// vs 0x20000+152 words=0x20260 in the packer) that never actually agreed
// with each other -- a real, found bug, unresolved when that top_pd_puf
// attempt stalled. This file and its packer both include
// secure_boot_7bank_layout.h instead, so the address can't silently
// diverge between them again.
//
// Also unlike rom_puf_secure_boot.c (written for top_pd_puf's real,
// separately-macro'd 256-word/1KiB DMEM), top_pd_7bank's DMEM is its own
// full 1792-word (7KiB) tlul_sram_if_macro_ocd_7bank instance (confirmed
// against rtl/top_pd_7bank.sv) -- there is no need to trim the payload
// down to fit a 256-word window here.
#include <stdint.h>
#include <stdbool.h>
#include "boot_hdr.h"
#include "secure_boot_7bank_layout_gls.h"
#include "./utils/uart.h"
#include "./utils/sha256.h"
#include "./utils/micro-ecc/uECC.h"

typedef void (*entry_fn_t)(void);

static inline uint32_t reg_read(uint32_t addr) { return *(volatile uint32_t *)addr; }
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
static void die(const char *msg) {
  uart_puts(msg);
  uart_puts("!\r\n"); // '!' sentinel -- same exit trigger the tb already uses
  while (1) { __asm__ volatile("wfi"); }
}

// ====== PUF-derived key (same derivation host_pack_7bank_image.c uses to sign) ======
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

// ====== reused verbatim (structure) from the real test_sw/c/rom.c ======
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
static void verify_header(const boot_hdr_t *h, uint32_t img_base, uint32_t expected_type) {
  if (h->magic != BOOT_MAGIC)        die("ROM: BAD HDR");
  if (h->hdr_version != HDR_VERSION) die("ROM: BAD HDR");
  if (h->hdr_len != sizeof(boot_hdr_t)) die("ROM: BAD HDR");
  if (h->img_type != expected_type)  die("ROM: BAD HDR");
  if ((h->payload_off & 3u) != 0)    die("ROM: BAD HDR");
  if ((h->sig_off & 3u) != 0)        die("ROM: BAD HDR");
  if ((h->load_addr & 3u) != 0)      die("ROM: BAD HDR");
  if ((h->entry_addr & 3u) != 0)     die("ROM: BAD HDR");
  if (h->sig_len != 40u)             die("ROM: BAD HDR"); // secp160r1: r||s, 20 bytes each

  uint32_t payload_src = img_base + h->payload_off;
  uint32_t sig_src     = img_base + h->sig_off;

  if (h->payload_off < h->hdr_len) die("ROM: BAD RANGE");
  if (!in_range_len(payload_src, h->payload_len, SB7_DMEM_BASE, SB7_DMEM_SIZE)) die("ROM: BAD RANGE");
  if (!in_range_len(sig_src, h->sig_len, SB7_DMEM_BASE, SB7_DMEM_SIZE))         die("ROM: BAD RANGE");
  if (!in_range_len(h->load_addr, h->payload_len, SB7_EXEC_BASE, SB7_EXEC_SIZE)) die("ROM: BAD RANGE");
  if (h->entry_addr < h->load_addr || h->entry_addr >= (h->load_addr + h->payload_len)) die("ROM: BAD RANGE");
}
static void copy_payload(uint32_t dst_addr, const uint8_t *src, uint32_t len) {
  volatile uint8_t *dst = (volatile uint8_t *)(uintptr_t)dst_addr;
  for (uint32_t i = 0; i < len; ++i) dst[i] = src[i];
}
static void jump_to(uint32_t entry_addr) {
  ((entry_fn_t)(uintptr_t)entry_addr)();
}

int main(void) {
  rng_state = 0x1u;

  uart_puts("ROM7: alive\r\n");

  uint8_t puf_key[32];
  read_puf_key(puf_key);
  uart_puts("ROM7: P");
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
  if (!found) die("ROM: NO KEY");
  uart_puts("ROM7: K\r\n"); // pubkey derived -- full hex dump trimmed to fit the real 7168B IMEM budget

  const uint32_t img_base = SB7_BOOT_IMG_BASE;
  const boot_hdr_t *h = (const boot_hdr_t *)(uintptr_t)img_base;
  verify_header(h, img_base, IMG_TYPE_BL0);

  const uint8_t *payload = (const uint8_t *)(uintptr_t)(img_base + h->payload_off);
  const uint8_t *sig     = (const uint8_t *)(uintptr_t)(img_base + h->sig_off);

  uint8_t digest[32];
  compute_digest(h, payload, digest);
  uart_puts("ROM7: D\r\n"); // digest computed -- full hex dump trimmed

  if (!uECC_verify(public_key, digest, 32, sig, curve)) {
    die("ROM: VERIFY FAIL");
  }
  uart_puts("ROM7: verify OK\r\n");

  copy_payload(h->load_addr, payload, h->payload_len);
  uart_puts("ROM7: jumping!\r\n");
  jump_to(h->entry_addr);

  die("ROM: NO RETURN");
  return 0;
}
