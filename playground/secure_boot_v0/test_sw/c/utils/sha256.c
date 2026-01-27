#include "sha256.h"

static uint32_t rotr32(uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); }
static uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z); }
static uint32_t maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
static uint32_t bsig0(uint32_t x) { return rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22); }
static uint32_t bsig1(uint32_t x) { return rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25); }
static uint32_t ssig0(uint32_t x) { return rotr32(x, 7) ^ rotr32(x, 18) ^ (x >> 3); }
static uint32_t ssig1(uint32_t x) { return rotr32(x, 17) ^ rotr32(x, 19) ^ (x >> 10); }

static const uint32_t K[64] = {
  0x428a2f98u,0x71374491u,0xb5c0fbcfu,0xe9b5dba5u,0x3956c25bu,0x59f111f1u,0x923f82a4u,0xab1c5ed5u,
  0xd807aa98u,0x12835b01u,0x243185beu,0x550c7dc3u,0x72be5d74u,0x80deb1feu,0x9bdc06a7u,0xc19bf174u,
  0xe49b69c1u,0xefbe4786u,0x0fc19dc6u,0x240ca1ccu,0x2de92c6fu,0x4a7484aau,0x5cb0a9dcu,0x76f988dau,
  0x983e5152u,0xa831c66du,0xb00327c8u,0xbf597fc7u,0xc6e00bf3u,0xd5a79147u,0x06ca6351u,0x14292967u,
  0x27b70a85u,0x2e1b2138u,0x4d2c6dfcu,0x53380d13u,0x650a7354u,0x766a0abbu,0x81c2c92eu,0x92722c85u,
  0xa2bfe8a1u,0xa81a664bu,0xc24b8b70u,0xc76c51a3u,0xd192e819u,0xd6990624u,0xf40e3585u,0x106aa070u,
  0x19a4c116u,0x1e376c08u,0x2748774cu,0x34b0bcb5u,0x391c0cb3u,0x4ed8aa4au,0x5b9cca4fu,0x682e6ff3u,
  0x748f82eeu,0x78a5636fu,0x84c87814u,0x8cc70208u,0x90befffau,0xa4506cebu,0xbef9a3f7u,0xc67178f2u
};

void sha256_init(sha256_ctx_t *c) {
  c->h[0]=0x6a09e667u; c->h[1]=0xbb67ae85u; c->h[2]=0x3c6ef372u; c->h[3]=0xa54ff53au;
  c->h[4]=0x510e527fu; c->h[5]=0x9b05688cu; c->h[6]=0x1f83d9abu; c->h[7]=0x5be0cd19u;
  c->len = 0;
  c->buf_len = 0;
}

static void sha256_block(sha256_ctx_t *c, const uint8_t b[64]) {
  uint32_t w[64];
  for (int i=0;i<16;i++) {
    w[i] = ((uint32_t)b[i*4+0]<<24) | ((uint32_t)b[i*4+1]<<16) |
           ((uint32_t)b[i*4+2]<<8)  | ((uint32_t)b[i*4+3]);
  }
  for (int i=16;i<64;i++) w[i] = ssig1(w[i-2]) + w[i-7] + ssig0(w[i-15]) + w[i-16];

  uint32_t a=c->h[0],b0=c->h[1],c0=c->h[2],d=c->h[3],e=c->h[4],f=c->h[5],g=c->h[6],h=c->h[7];
  for (int i=0;i<64;i++) {
    uint32_t t1 = h + bsig1(e) + ch(e,f,g) + K[i] + w[i];
    uint32_t t2 = bsig0(a) + maj(a,b0,c0);
    h=g; g=f; f=e; e=d+t1; d=c0; c0=b0; b0=a; a=t1+t2;
  }
  c->h[0]+=a; c->h[1]+=b0; c->h[2]+=c0; c->h[3]+=d; c->h[4]+=e; c->h[5]+=f; c->h[6]+=g; c->h[7]+=h;
}

void sha256_update(sha256_ctx_t *c, const uint8_t *p, uint32_t n) {
  c->len += (uint64_t)n;
  while (n) {
    uint32_t take = 64 - c->buf_len;
    if (take > n) take = n;
    for (uint32_t i=0;i<take;i++) c->buf[c->buf_len+i] = p[i];
    c->buf_len += take;
    p += take; n -= take;
    if (c->buf_len == 64) {
      sha256_block(c, c->buf);
      c->buf_len = 0;
    }
  }
}

void sha256_final(sha256_ctx_t *c, uint8_t out[32]) {
  uint64_t bitlen = c->len * 8u;
  c->buf[c->buf_len++] = 0x80;
  while (c->buf_len != 56) {
    if (c->buf_len == 64) { sha256_block(c, c->buf); c->buf_len = 0; }
    c->buf[c->buf_len++] = 0x00;
  }
  for (int i=7;i>=0;i--) c->buf[c->buf_len++] = (uint8_t)(bitlen >> (i*8));
  sha256_block(c, c->buf);

  for (int i=0;i<8;i++) {
    out[i*4+0] = (uint8_t)(c->h[i] >> 24);
    out[i*4+1] = (uint8_t)(c->h[i] >> 16);
    out[i*4+2] = (uint8_t)(c->h[i] >> 8);
    out[i*4+3] = (uint8_t)(c->h[i]);
  }
}
