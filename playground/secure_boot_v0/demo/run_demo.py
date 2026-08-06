#!/usr/bin/env python3
import sys
sys.path.insert(0, '/foss/designs/opentitan_minrot_nix/playground/secure_boot_v0/demo')
from puf_to_key import load_puf_bits, puf_to_key

csv_path = sys.argv[1]
chip_id = int(sys.argv[2])
fifo_path = sys.argv[3]

bits = load_puf_bits(csv_path, chip_id)
key = puf_to_key(bits)
key_hex = key.hex()

print(f"Chip {chip_id} PUF bits: {bits}")
print(f"Derived key: {key_hex} ({len(key)} bytes)")

with open(fifo_path, 'wb') as f:
    f.write(key)
    f.flush()

print(f"Sent {len(key)} bytes over {fifo_path}")
