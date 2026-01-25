import struct, sys

data = open(sys.argv[1], "rb").read()
data += b"\x00" * ((4 - (len(data) % 4)) % 4)  # pad to 4B

for i in range(0, len(data), 4):
    w = struct.unpack("<I", data[i:i+4])[0]  # little-endian
    print(f"{w:08x}")
