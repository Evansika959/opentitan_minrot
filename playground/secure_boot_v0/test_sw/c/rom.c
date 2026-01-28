// rom.c
#include <stdint.h>
#include <stdbool.h>
#include "boot_hdr.h"
#include "./utils/uart.h"
#include "./utils/sha256.h"
#include "./utils/trusted_pubkey.h"

// ====== ECDSA verify via micro-ecc ======
#include "./utils/micro-ecc/uECC.h"

// ====== Platform constants (adjust if your map differs) ======
#define DATA_SRAM_BASE   0x00020000u
#define DATA_SRAM_SIZE   0x00010000u   // 64KB

#define EXEC_BASE        0x00010000u
#define EXEC_SIZE        0x00010000u   // 64KB

#define BOOT_IMG_BASE    0x00021000u   // ROM_EXT image container base in D-SRAM
#define BL0_IMG_BASE     0x00023000u   // BL0 image container base in D-SRAM

// #define FAST_SIM  // Skip payload hashing in FAST_SIM to speed up runs

typedef void (*entry_fn_t)(void);

// Forward declarations (definitions after main)
static void uart_puts(const char *s);
static void die(const char *msg);
static bool add_overflow_u32(uint32_t a, uint32_t b, uint32_t *out);
static bool in_range_len(uint32_t addr, uint32_t len, uint32_t base, uint32_t size);
static void compute_digest(const boot_hdr_t *h, const uint8_t *payload, uint8_t digest[32]);
static void verify_header(const boot_hdr_t *h, uint32_t img_base, uint32_t expected_type);
static void copy_payload(uint32_t dst_addr, const uint8_t *src, uint32_t len);
static void jump_to(uint32_t entry_addr);
static void uart_put_hex32(uint32_t v);
static void uart_put_hex8(uint8_t v);

// void rom_main(void) {
int main(void) {
  uart_putc('s');

  const uint32_t img_base = BOOT_IMG_BASE;
  const boot_hdr_t *h = (const boot_hdr_t *)(uintptr_t)img_base;

  // uart_putc('m');
  // uart_put_hex32(h->magic);
  // uart_putc('m');

  // verify_header(h, img_base, IMG_TYPE_ROM_EXT);

  const uint8_t *payload = (const uint8_t *)(uintptr_t)(img_base + h->payload_off);
  const uint8_t *sig     = (const uint8_t *)(uintptr_t)(img_base + h->sig_off);
  
  // uint8_t digest[32];

  // // print the payload length
  // uart_putc('t');
  // uart_put_hex32(h->sig_len);
  // uart_putc('t');
  // uart_put_hex32(h->load_addr);
  // uart_putc('t');
  // uart_put_hex32(h->payload_len);
  // uart_putc('t');

  // In FAST_SIM, skip payload hashing to speed up runs; still hash header for structure integrity.
  // #ifdef FAST_SIM
  //   hdr_bind_t bind = {
  //     .img_type    = h->img_type,
  //     .payload_len = h->payload_len,
  //     .load_addr   = h->load_addr,
  //     .entry_addr  = h->entry_addr,
  //   };
  //   sha256_ctx_t ctx_fast;
  //   sha256_init(&ctx_fast);
  //   sha256_update(&ctx_fast, (const uint8_t *)&bind, sizeof(bind));
  //   sha256_final(&ctx_fast, digest);
  // #else
  //   compute_digest(h, payload, digest);
  // #endif
  // uart_putc('c');

  // Print the digest 
  // for (int i = 0; i < 32; ++i) {
  //   uart_put_hex8(digest[i]);
  // }
  // uart_putc('\n');

  // micro-ecc expects pubkey as 64 bytes X||Y big-endian; signature as 64 bytes r||s big-endian.
  // if (!uECC_verify(TRUSTED_PUBKEY_XY, digest, 32, sig, uECC_secp256r1())) {
  //   die("ROM: ROM_EXT FAIL");
  // }

  uart_putc('J');
  copy_payload(h->load_addr, payload, h->payload_len);
  uart_putc('P');

  jump_to(h->entry_addr);

  // Emit "O" and halt without storing the string
  uart_putc('O');
  while (1) { __asm__ volatile("wfi"); }
}

// ====== UART ======
static void uart_puts(const char *s) {
  while (*s) uart_putc(*s++);
}

static void die(const char *msg) {
  uart_puts(msg);
  uart_puts("\n");
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
  if (h->magic != BOOT_MAGIC) die("ROM: BAD MAGIC");
  if (h->hdr_version != HDR_VERSION) die("ROM: BAD HDR VER");
  if (h->hdr_len != sizeof(boot_hdr_t)) die("ROM: BAD HDR LEN");
  if (h->img_type != expected_type) die("ROM: BAD IMG TYPE");
  if ((h->payload_off & 3u) != 0) die("ROM: PAYLOAD ALIGN");
  if ((h->sig_off & 3u) != 0) die("ROM: SIG ALIGN");
  if ((h->load_addr & 3u) != 0) die("ROM: LOAD ALIGN");
  if ((h->entry_addr & 3u) != 0) die("ROM: ENTRY ALIGN");
  if (h->sig_len != 64u) die("ROM: SIG LEN");

  // payload and sig must lie within D-SRAM (image storage)
  uint32_t payload_src = img_base + h->payload_off;
  uint32_t sig_src     = img_base + h->sig_off;

  if (h->payload_off < h->hdr_len) die("ROM: PAYLOAD OVERLAP");
  if (!in_range_len(payload_src, h->payload_len, DATA_SRAM_BASE, DATA_SRAM_SIZE)) die("ROM: PAYLOAD OOB");
  if (!in_range_len(sig_src, h->sig_len, DATA_SRAM_BASE, DATA_SRAM_SIZE)) die("ROM: SIG OOB");

  // destination must lie within EXEC SRAM
  if (!in_range_len(h->load_addr, h->payload_len, EXEC_BASE, EXEC_SIZE)) die("ROM: LOAD OOB");

  // entry must lie within loaded payload
  if (h->entry_addr < h->load_addr || h->entry_addr >= (h->load_addr + h->payload_len)) die("ROM: ENTRY OOB");

  uart_putc('v');
}

static void copy_payload(uint32_t dst_addr, const uint8_t *src, uint32_t len) {
  volatile uint8_t *dst = (volatile uint8_t *)(uintptr_t)dst_addr;
  for (uint32_t i = 0; i < len; ++i) {
    dst[i] = src[i];
  }
  // __asm__ volatile("fence.i"); // ensure copied instructions are visible to I-fetch
}

static void jump_to(uint32_t entry_addr) {
  ((entry_fn_t)(uintptr_t)entry_addr)();
}

static void uart_put_hex32(uint32_t v) {
  for (int i = 7; i >= 0; --i) {
    uint8_t nibble = (v >> (i * 4)) & 0xF;
    char c = (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
    uart_putc(c);
  }
}

static void uart_put_hex8(uint8_t v) {
  uint8_t hi = (v >> 4) & 0xF;
  uint8_t lo = v & 0xF;
  uart_putc((hi < 10) ? ('0' + hi) : ('A' + (hi - 10)));
  uart_putc((lo < 10) ? ('0' + lo) : ('A' + (lo - 10)));
}
