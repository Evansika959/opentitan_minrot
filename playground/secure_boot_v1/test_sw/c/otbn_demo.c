// otbn_demo.c
// Minimal host-side OTBN test using the OTBN register map.
// Loads a tiny OTBN program (ECALL) into IMEM, executes it, and checks ERR_BITS.

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "./utils/uart.h"

#ifndef OTBN_BASE_ADDR
#define OTBN_BASE_ADDR 0x00050000u // Update if your memory map differs
#endif

// ---------- Register offsets (bytes) ----------
#define OTBN_INTR_STATE_OFF   0x000u
#define OTBN_CMD_OFF          0x010u
#define OTBN_STATUS_OFF       0x018u
#define OTBN_ERR_BITS_OFF     0x01Cu
#define OTBN_FATAL_ALERT_CAUSE_OFF 0x020u
#define OTBN_LOAD_CHKSUM_OFF  0x028u
#define OTBN_IMEM_OFF         0x4000u
#define OTBN_DMEM_OFF         0x8000u

// ---------- INTR_STATE bits ----------
#define OTBN_INTR_DONE_BIT 0

// ---------- CMD values ----------
#define OTBN_CMD_EXECUTE 0xD8u

// ---------- STATUS values ----------
#define OTBN_STATUS_IDLE   0x00u
#define OTBN_STATUS_LOCKED 0xFFu

// ---------- Tiny MMIO helpers ----------
static inline void mmio_write32(uint32_t addr, uint32_t val);
static inline uint32_t mmio_read32(uint32_t addr);

static void otbn_wait_idle(void);
static void otbn_clear_done(void);
static void otbn_clear_err_bits(void);
static void otbn_load_imem(const uint32_t *words, size_t word_count);
static void otbn_load_dmem(const uint32_t *words, size_t word_count);
static void otbn_execute_and_wait(void);

int main(void) {
  otbn_wait_idle();

  uart_putc('o');

  // Minimal OTBN program: ECALL (signals completion).
  // ECALL encoding is 0x00000073 in the OTBN ISA base subset.
  static const uint32_t kImemImage[] = {
    0x00000073u
  };

  // Optional DMEM init (empty for this demo).
  static const uint32_t kDmemImage[] = { };

  otbn_wait_idle();
  otbn_clear_done();
  otbn_clear_err_bits();

  uint32_t intr = mmio_read32(OTBN_BASE_ADDR + OTBN_INTR_STATE_OFF);
//   uart_put_hex32(intr);

  uart_putc('1');

  mmio_write32(OTBN_BASE_ADDR + OTBN_LOAD_CHKSUM_OFF, 0u);

  otbn_load_imem(kImemImage, sizeof(kImemImage) / sizeof(kImemImage[0]));
  otbn_load_dmem(kDmemImage, 0u);

  uart_putc('2');
  otbn_execute_and_wait();

  uint32_t err = mmio_read32(OTBN_BASE_ADDR + OTBN_ERR_BITS_OFF);
  if (err == 0u) {
    uart_putc('P');
  } else {
    uart_putc('E');
    uart_put_hex32(err);
  }

  while (1) { __asm__ volatile("wfi"); }
}

// ---------- Tiny MMIO helpers ----------
static inline void mmio_write32(uint32_t addr, uint32_t val) {
  *(volatile uint32_t *)addr = val;
}

static inline uint32_t mmio_read32(uint32_t addr) {
  return *(volatile uint32_t *)addr;
}

static void otbn_wait_idle(void) {
  while (1) {
    uint32_t st = mmio_read32(OTBN_BASE_ADDR + OTBN_STATUS_OFF);
    if (st == OTBN_STATUS_IDLE) {
      return;
    }
    if (st == OTBN_STATUS_LOCKED) {
      uint32_t err = mmio_read32(OTBN_BASE_ADDR + OTBN_ERR_BITS_OFF);
      uint32_t fac = mmio_read32(OTBN_BASE_ADDR + OTBN_FATAL_ALERT_CAUSE_OFF);
      uart_puts("L");
      uart_putc('E');
      uart_put_hex32(err);
      uart_putc('F');
      uart_put_hex32(fac);
      while (1) { __asm__ volatile("wfi"); }
    }
  }
}

static void otbn_clear_done(void) {
  mmio_write32(OTBN_BASE_ADDR + OTBN_INTR_STATE_OFF, (1u << OTBN_INTR_DONE_BIT));
}

static void otbn_clear_err_bits(void) {
  mmio_write32(OTBN_BASE_ADDR + OTBN_ERR_BITS_OFF, 0xFFFFFFFFu);
}

static void otbn_load_imem(const uint32_t *words, size_t word_count) {
  for (size_t i = 0; i < word_count; i++) {
    mmio_write32(OTBN_BASE_ADDR + OTBN_IMEM_OFF + (uint32_t)(4u * i), words[i]);
  }
}

static void otbn_load_dmem(const uint32_t *words, size_t word_count) {
  for (size_t i = 0; i < word_count; i++) {
    mmio_write32(OTBN_BASE_ADDR + OTBN_DMEM_OFF + (uint32_t)(4u * i), words[i]);
  }
}

static void otbn_execute_and_wait(void) {
  mmio_write32(OTBN_BASE_ADDR + OTBN_CMD_OFF, OTBN_CMD_EXECUTE);
  uint32_t st = mmio_read32(OTBN_BASE_ADDR + OTBN_STATUS_OFF);
  uint32_t err = mmio_read32(OTBN_BASE_ADDR + OTBN_ERR_BITS_OFF);
  uart_putc('S');
  uart_put_hex32(st);
  uart_putc('E');
  uart_put_hex32(err);
  uint32_t spin = 0;
  while (1) {
    uint32_t intr = mmio_read32(OTBN_BASE_ADDR + OTBN_INTR_STATE_OFF);
    if (spin == 0x10u) {
      uint32_t st2 = mmio_read32(OTBN_BASE_ADDR + OTBN_STATUS_OFF);
      uint32_t err2 = mmio_read32(OTBN_BASE_ADDR + OTBN_ERR_BITS_OFF);
      uart_putc('s');
      uart_put_hex32(st2);
      uart_putc('e');
      uart_put_hex32(err2);
    }
    spin++;
    if (intr & (1u << OTBN_INTR_DONE_BIT)) {
      return;
    }
  }
}
