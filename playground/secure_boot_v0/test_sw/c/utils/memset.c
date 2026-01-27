#include <stdint.h>
#include <stddef.h>

__attribute__((optimize("O0"), noinline))
void *memset(void *dest, int c, size_t n) {
  uint8_t *p = (uint8_t *)dest;
  uint8_t v = (uint8_t)c;
  for (size_t i = 0; i < n; ++i) {
    p[i] = v;
  }
  return dest;
}
