#ifndef SW_UTILS_SHA256_H_
#define SW_UTILS_SHA256_H_

#include <stdint.h>

typedef struct {
  uint32_t h[8];
  uint64_t len;
  uint8_t  buf[64];
  uint32_t buf_len;
} sha256_ctx_t;

void sha256_init(sha256_ctx_t *c);
void sha256_update(sha256_ctx_t *c, const uint8_t *p, uint32_t n);
void sha256_final(sha256_ctx_t *c, uint8_t out[32]);

#endif // SW_UTILS_SHA256_H_
