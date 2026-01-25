#include <stdint.h>
#include <stdbool.h>

// DMEM is mapped at 0x0002_0000 via the TL-UL xbar (see link.ld / top.sv).
// This test writes a small pattern into a scratch window of DMEM and
// verifies it can be read back.

#define DMEM_BASE      0x00020000u
#define TEST_OFFSET    0x00000100u  // keep clear of .data/.bss and stack
#define TEST_WORDS     16

// Status location you can probe in waves or memory.
#define STATUS_OFFSET  0x00000080u

static inline uint32_t pattern(uint32_t idx) {
  return 0xA5A50000u ^ (idx * 0x1111u);
}

static bool dmem_selftest(void) {
  volatile uint32_t *const win = (uint32_t *)(DMEM_BASE + TEST_OFFSET);

  // Write phase
  for (uint32_t i = 0; i < TEST_WORDS; ++i) {
    win[i] = pattern(i);
  }

  // Read/verify phase
  for (uint32_t i = 0; i < TEST_WORDS; ++i) {
    uint32_t exp = pattern(i);
    uint32_t got = win[i];
    if (got != exp) {
      return false;
    }
  }

  return true;
}

int main(void) {
  volatile uint32_t *const status = (uint32_t *)(DMEM_BASE + STATUS_OFFSET);
  bool ok = dmem_selftest();

  // 0x1 = pass; 0xDEAD0000 | failing index would be used if we reported more detail.
  *status = ok ? 0x1u : 0xDEAD0000u;

  // Idle forever; inspect STATUS_OFFSET and TEST_OFFSET region in waves or memory.
  while (1) {
    // spin
  }
  return 0;
}
