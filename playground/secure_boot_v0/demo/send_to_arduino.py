#!/usr/bin/env python3
import os
import sys, time, serial
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from puf_to_key import load_puf_bits, puf_to_key

def main():
    csv_path = sys.argv[1]
    chip_id = int(sys.argv[2])
    port = sys.argv[3]

    bits = load_puf_bits(csv_path, chip_id)
    key = puf_to_key(bits)  # 32 bytes, SHA-256

    print(f"Chip {chip_id} PUF bits: {bits}")
    print(f"Derived key: {key.hex()}")

    ser = serial.Serial(port, 115200, timeout=5)
    time.sleep(2)  # let Arduino reset after serial connect, standard practice
    ser.write(key[:21])  # send first 21 bytes (secp160r1 private key size)
    print(f"Sent 21 bytes to {port}")

    response = ser.readline().decode(errors='replace').strip()
    print(f"Arduino response: {response}")
    ser.close()

if __name__ == "__main__":
    main()
