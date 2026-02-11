// hmac_sha256_reg_demo.c
// Register-level SHA-256 ("no-key hashing") using OpenTitan HMAC IP.
//
// Sequence (per OpenTitan docs):
//  - wait idle
//  - CFG: sha_en=1, hmac_en=0 (SHA mode)
//  - CMD.hash_start
//  - write bytes to MSG_FIFO window
//  - CMD.hash_process (finalize)
//  - wait for INTR_STATE.hmac_done
//  - read DIGEST_0..7

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef HMAC_BASE_ADDR
#define HMAC_BASE_ADDR 0x00031000u  // <-- set to your memory map
#endif

// ---------- Register offsets (bytes) ----------
#define HMAC_INTR_STATE_OFF   0x000u
#define HMAC_CFG_OFF          0x010u
#define HMAC_CMD_OFF          0x014u
#define HMAC_STATUS_OFF       0x018u
#define HMAC_ERR_CODE_OFF     0x01Cu

#define HMAC_DIGEST0_OFF      0x0A4u  // DIGEST_0 starts here; 32-bit stride
#define HMAC_MSG_FIFO_OFF     0x1000u // MSG_FIFO window [0x1000..0x1ffc]

// ---------- Bit positions ----------
#define HMAC_INTR_HMAC_DONE_BIT 0
#define HMAC_INTR_HMAC_ERR_BIT  2

// CFG fields: [3]=digest_swap, [2]=endian_swap, [1]=sha_en, [0]=hmac_en
#define HMAC_CFG_HMAC_EN_BIT    0
#define HMAC_CFG_SHA_EN_BIT     1
#define HMAC_CFG_ENDIAN_SWAP_BIT 2
#define HMAC_CFG_DIGEST_SWAP_BIT 3

// CMD fields: [0]=hash_start, [1]=hash_process, [2]=hash_stop, [3]=hash_continue
#define HMAC_CMD_HASH_START_BIT   0
#define HMAC_CMD_HASH_PROCESS_BIT 1

// STATUS fields: [0]=hmac_idle, [1]=fifo_empty, [2]=fifo_full, [9:4]=fifo_depth
#define HMAC_STATUS_HMAC_IDLE_BIT 0
#define HMAC_STATUS_FIFO_FULL_BIT 2

// ---------- Tiny MMIO helpers ----------
static inline void mmio_write32(uint32_t addr, uint32_t val) {
  *(volatile uint32_t *)addr = val;
}
static inline uint32_t mmio_read32(uint32_t addr) {
  return *(volatile uint32_t *)addr;
}
static inline void mmio_write8(uint32_t addr, uint8_t val) {
  *(volatile uint8_t *)addr = val;
}

// ---------- UART hooks: replace with your UART (optional) ----------
static void uart_puthex4(uint8_t v) {
  v &= 0xF;
  uart_putc((v < 10) ? ('0' + v) : ('a' + (v - 10)));
}
static void uart_puthex8(uint8_t v) { uart_puthex4(v >> 4); uart_puthex4(v); }
static void uart_puthex_buf(const uint8_t *buf, size_t len) {
  for (size_t i = 0; i < len; i++) uart_puthex8(buf[i]);
}

static void die(const char *msg) {
  uart_puts("FATAL: "); uart_puts(msg); uart_puts("\n");
  while (1) { __asm__ volatile("wfi"); }
}

// Clear done/err by RW1C writes to INTR_STATE
static void hmac_intr_clear(uint32_t mask) {
  mmio_write32(HMAC_BASE_ADDR + HMAC_INTR_STATE_OFF, mask);
}

static void hmac_wait_idle(void) {
  while (((mmio_read32(HMAC_BASE_ADDR + HMAC_STATUS_OFF) >> HMAC_STATUS_HMAC_IDLE_BIT) & 1u) == 0u) {}
}

// Optional: avoid backpressure by waiting when FIFO is full
static void hmac_wait_fifo_not_full(void) {
  while (((mmio_read32(HMAC_BASE_ADDR + HMAC_STATUS_OFF) >> HMAC_STATUS_FIFO_FULL_BIT) & 1u) != 0u) {}
}

// Write arbitrary bytes into MSG_FIFO window. The HMAC IP supports byte writes;
// only the low [1:0] address bits matter within the MSG_FIFO window. :contentReference[oaicite:1]{index=1}
static void hmac_write_msg_bytes(const uint8_t *data, size_t len) {
  for (size_t i = 0; i < len; i++) {
    hmac_wait_fifo_not_full();
    // Use low bits to make byte writes well-defined.
    uint32_t a = HMAC_BASE_ADDR + HMAC_MSG_FIFO_OFF + (uint32_t)(i & 3u);
    mmio_write8(a, data[i]);
  }
}

static void hmac_sha256_reg(const uint8_t *msg, size_t msg_len, uint8_t out32[32]) {
  // 0) Ensure idle, clear previous interrupts/errors
  hmac_wait_idle();
  hmac_intr_clear((1u << HMAC_INTR_HMAC_DONE_BIT) | (1u << HMAC_INTR_HMAC_ERR_BIT));

  // 1) Configure for SHA mode: sha_en=1, hmac_en=0, no swaps.
  // CFG fields/offset documented here. :contentReference[oaicite:2]{index=2}
  uint32_t cfg = 0;
  cfg |= (1u << HMAC_CFG_SHA_EN_BIT);     // enable SHA engine
  cfg |= (0u << HMAC_CFG_HMAC_EN_BIT);    // disable HMAC mode (no key)
  cfg |= (0u << HMAC_CFG_ENDIAN_SWAP_BIT);
  cfg |= (0u << HMAC_CFG_DIGEST_SWAP_BIT);
  mmio_write32(HMAC_BASE_ADDR + HMAC_CFG_OFF, cfg);

  // 2) Start hashing stream
  // CMD.hash_start documented here. :contentReference[oaicite:3]{index=3}
  mmio_write32(HMAC_BASE_ADDR + HMAC_CMD_OFF, (1u << HMAC_CMD_HASH_START_BIT));

  // 3) Write message bytes
  hmac_write_msg_bytes(msg, msg_len);

  // 4) Finalize (process)
  // Programmer’s guide says finalize by setting CMD.hash_process. :contentReference[oaicite:4]{index=4}
  mmio_write32(HMAC_BASE_ADDR + HMAC_CMD_OFF, (1u << HMAC_CMD_HASH_PROCESS_BIT));

  // 5) Wait for done or error
  while (1) {
    uint32_t intr = mmio_read32(HMAC_BASE_ADDR + HMAC_INTR_STATE_OFF);
    if (intr & (1u << HMAC_INTR_HMAC_ERR_BIT)) {
      uint32_t err = mmio_read32(HMAC_BASE_ADDR + HMAC_ERR_CODE_OFF);
      (void)err;
      die("HMAC error (see ERR_CODE)");
    }
    if (intr & (1u << HMAC_INTR_HMAC_DONE_BIT)) break;
  }

  // Clear done
  hmac_intr_clear(1u << HMAC_INTR_HMAC_DONE_BIT);

  // 6) Read digest words DIGEST_0..7 for SHA-256
  // Digest ordering: SHA-256 uses DIGEST_0..DIGEST_7. :contentReference[oaicite:5]{index=5}
  for (uint32_t i = 0; i < 8; i++) {
    uint32_t w = mmio_read32(HMAC_BASE_ADDR + HMAC_DIGEST0_OFF + 4u * i);

    // With digest_swap=0, interpret as big-endian bytes per 32-bit word
    out32[4*i + 0] = (uint8_t)(w >> 24);
    out32[4*i + 1] = (uint8_t)(w >> 16);
    out32[4*i + 2] = (uint8_t)(w >> 8);
    out32[4*i + 3] = (uint8_t)(w >> 0);
  }
}

static bool buf_equal(const uint8_t *a, const uint8_t *b, size_t n) {
  uint8_t diff = 0;
  for (size_t i = 0; i < n; i++) diff |= (a[i] ^ b[i]);
  return diff == 0;
}

int main(void) {
  uart_putc("s");

  static const uint8_t msg[] = {'a','b','c'};
  uint8_t digest[32];
  hmac_sha256_reg(msg, sizeof(msg), digest);

  uart_putc("1");
  uart_puthex_buf(digest, 32);
  uart_putc("2");

  // Expected SHA-256("abc")
  static const uint8_t exp[32] = {
    0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,
    0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
    0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,
    0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad
  };

  uart_puts(buf_equal(digest, exp, 32) ? "PASS\n" : "FAIL\n");
  while (1) { __asm__ volatile("wfi"); }
}
