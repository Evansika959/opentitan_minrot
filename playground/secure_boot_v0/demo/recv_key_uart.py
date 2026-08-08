#!/usr/bin/env python3
import sys

def recv_key(fifo_path, num_bytes=32):
    with open(fifo_path, 'rb') as f:
        data = f.read(num_bytes)
    print(f"Received {len(data)} bytes over {fifo_path}: {data.hex()}")
    return data

if __name__ == "__main__":
    recv_key(sys.argv[1])
