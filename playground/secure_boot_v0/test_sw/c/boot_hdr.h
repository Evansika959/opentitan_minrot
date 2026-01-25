// boot_hdr.h
#pragma once
#include <stdint.h>

#define BOOT_MAGIC 0x30474D49u  // "IMG0" little-endian: I M G 0
#define HDR_VERSION 1u

typedef enum {
  IMG_TYPE_ROM_EXT = 1,
  IMG_TYPE_BL0     = 2,
} img_type_t;

// What we bind into the signature (prevents "verify payload but change jump addr").
typedef struct __attribute__((packed)) {
  uint32_t img_type;
  uint32_t payload_len;
  uint32_t load_addr;
  uint32_t entry_addr;
} hdr_bind_t;

// Fixed-size 64B header for simplicity and stable offsets.
typedef struct __attribute__((packed, aligned(4))) {
  uint32_t magic;        // BOOT_MAGIC
  uint16_t hdr_version;  // HDR_VERSION
  uint16_t hdr_len;      // sizeof(boot_hdr_t) == 64

  uint32_t img_type;     // 1=ROM_EXT, 2=BL0
  uint32_t payload_off;  // offset from IMG_BASE to payload (bytes)
  uint32_t payload_len;  // payload bytes length

  uint32_t load_addr;    // where to copy payload (EXEC_BASE typically)
  uint32_t entry_addr;   // where to jump (within loaded payload)

  uint32_t sig_off;      // offset from IMG_BASE to signature
  uint32_t sig_len;      // signature length (64 for raw r||s)

  uint32_t reserved[7];  // pad to 64 bytes total
} boot_hdr_t;

_Static_assert(sizeof(boot_hdr_t) == 64, "boot_hdr_t must be 64 bytes");
_Static_assert(sizeof(hdr_bind_t) == 16, "hdr_bind_t must be 16 bytes");
