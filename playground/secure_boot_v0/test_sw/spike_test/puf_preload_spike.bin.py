#!/usr/bin/env python3
# puf_preload_spike.bin.py -- writes the same known SPICE-derived PUF bytes
# host_pack_7bank_image_spike.c signs with, as a raw 32-byte binary, for
# injection into spike's memory at PUF_BASE+4 (0x80040004). Without this,
# read_puf_key() reads all-zero (spike has no PUF hardware, just plain
# memory that was never written), producing an invalid all-zero EC scalar
# and a legitimate "ROM: NO KEY" failure -- not a ROM logic bug, a missing
# test fixture. The real GLS run does this correctly already via
# +gls_realdata_hex=.
import struct
puf_key = bytes([
  0x23,0xD9,0xC2,0x92,0x51,0x3E,0x76,0x32,
  0x7C,0x0E,0x65,0x36,0x10,0x14,0x20,0x91,
  0x94,0x13,0x50,0x07,0x01,0x78,0x02,0x82,
  0x0E,0x51,0x81,0x88,0xC4,0x44,0x35,0x0A,
])
import sys
with open(sys.argv[1], "wb") as f:
    f.write(puf_key)
