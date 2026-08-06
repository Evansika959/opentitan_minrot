#!/usr/bin/env python3
import sys

def send_key(fifo_path, key_hex):
    key_bytes = bytes.fromhex(key_hex)
    with open(fifo_path, 'wb') as f:
        f.write(key_bytes)
        f.flush()
    print(f"Sent {len(key_bytes)} bytes over {fifo_path}: {key_hex}")

if __name__ == "__main__":
    send_key(sys.argv[1], sys.argv[2])
