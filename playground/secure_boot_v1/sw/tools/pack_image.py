#!/usr/bin/env python3
import argparse, os, struct, subprocess, tempfile

BOOT_MAGIC = 0x30474D49  # "IMG0"
HDR_VERSION = 1
HDR_LEN = 64
SIG_LEN = 64  # raw r||s

IMG_TYPE_ROM_EXT = 1
IMG_TYPE_BL0 = 2

DATA_SRAM_BASE = 0x20000
DATA_SRAM_SIZE = 0x10000

BOOT_IMG_BASE = 0x21000
BL0_IMG_BASE  = 0x23000
EXEC_BASE     = 0x10000
BL0_ENTRY_BASE = EXEC_BASE + 0x2000

def run(cmd):
    r = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if r.returncode != 0:
        raise RuntimeError(f"Command failed: {' '.join(cmd)}\nSTDOUT:\n{r.stdout}\nSTDERR:\n{r.stderr}")
    return r.stdout

def align_up(x, a):
    return (x + (a-1)) & ~(a-1)

def parse_ecdsa_der_to_raw(der: bytes) -> bytes:
    # DER: 30 LL 02 LR R 02 LS S
    if len(der) < 8 or der[0] != 0x30:
        raise ValueError("Not a DER SEQUENCE")
    idx = 2
    if der[1] & 0x80:
        nlen = der[1] & 0x7f
        idx = 2 + nlen

    if der[idx] != 0x02: raise ValueError("Expected INTEGER r")
    lr = der[idx+1]
    r = der[idx+2:idx+2+lr]
    idx = idx+2+lr
    if der[idx] != 0x02: raise ValueError("Expected INTEGER s")
    ls = der[idx+1]
    s = der[idx+2:idx+2+ls]

    # Strip leading 0x00 if present (sign bit)
    r = r[1:] if len(r) > 0 and r[0] == 0x00 else r
    s = s[1:] if len(s) > 0 and s[0] == 0x00 else s
    if len(r) > 32 or len(s) > 32:
        raise ValueError("r or s too large for P-256")

    r = r.rjust(32, b"\x00")
    s = s.rjust(32, b"\x00")
    return r + s

def extract_pubkey_xy_from_pem(pub_pem: str) -> bytes:
    # Use openssl text output to avoid fragile DER parsing. Expect uncompressed point: 0x04 || X || Y
    out = run(["openssl", "ec", "-pubin", "-in", pub_pem, "-text", "-noout"])
    hex_lines = []
    grab = False
    for line in out.splitlines():
        line = line.strip()
        if line.startswith("pub:"):
            grab = True
            continue
        if grab:
            if line.startswith("ASN1") or line.startswith("NIST"):
                break
            hex_lines.extend(line.replace(":", " ").split())
    pub_bytes = bytes(int(h, 16) for h in hex_lines)
    if len(pub_bytes) != 65 or pub_bytes[0] != 0x04:
        raise ValueError("Expected uncompressed EC point 65 bytes from openssl ec -text")
    return pub_bytes[1:33] + pub_bytes[33:65]

def make_header(img_type, payload_off, payload_len, load_addr, entry_addr, sig_off, sig_len):
    # boot_hdr_t: see boot_hdr.h
    reserved = [0]*7
    return struct.pack(
        "<IHHIIIIIII7I",
        BOOT_MAGIC, HDR_VERSION, HDR_LEN,
        img_type, payload_off, payload_len,
        load_addr, entry_addr,
        sig_off, sig_len,
        *reserved
    )

def make_header_exact(img_type, payload_off, payload_len, load_addr, entry_addr, sig_off, sig_len):
    # Exactly matches boot_hdr_t:
    # magic (I), hdr_version (H), hdr_len (H),
    # img_type(I), payload_off(I), payload_len(I),
    # load_addr(I), entry_addr(I),
    # sig_off(I), sig_len(I),
    # reserved[7] (7I)
    reserved = [0]*7
    return struct.pack(
        "<IHHIIIIIII7I",
        BOOT_MAGIC, HDR_VERSION, HDR_LEN,
        img_type, payload_off, payload_len,
        load_addr, entry_addr,
        sig_off, sig_len,
        *reserved
    )

def hdr_bind_bytes(img_type, payload_len, load_addr, entry_addr):
    # hdr_bind_t packed little-endian 4x u32
    return struct.pack("<IIII", img_type, payload_len, load_addr, entry_addr)

def sign_with_openssl(priv_pem: str, msg: bytes) -> bytes:
    with tempfile.TemporaryDirectory() as td:
        msg_path = os.path.join(td, "msg.bin")
        sig_path = os.path.join(td, "sig.der")
        open(msg_path, "wb").write(msg)
        # ECDSA signature over SHA-256(msg), output DER
        run(["openssl", "dgst", "-sha256", "-sign", priv_pem, "-out", sig_path, msg_path])
        der = open(sig_path, "rb").read()
    return parse_ecdsa_der_to_raw(der)

def build_image(img_type, payload: bytes, load_addr, entry_addr, priv_pem):
    payload_off = HDR_LEN
    payload_len = len(payload)
    sig_off = align_up(payload_off + payload_len, 4)
    sig_len = SIG_LEN

    header = make_header_exact(img_type, payload_off, payload_len, load_addr, entry_addr, sig_off, sig_len)

    # Bind header fields into signature (hdr_bind_t || payload)
    bind = hdr_bind_bytes(img_type, payload_len, load_addr, entry_addr)
    sig_raw = sign_with_openssl(priv_pem, bind + payload)
    assert len(sig_raw) == 64

    # Construct container: header + payload + padding + sig_raw
    pad_len = sig_off - (payload_off + payload_len)
    image = header + payload + (b"\x00"*pad_len) + sig_raw
    return image

def write_memh_words_le(path, mem_bytes: bytes):
    # Output one 32-bit little-endian word per line as 8 hex chars.
    if len(mem_bytes) % 4 != 0:
        mem_bytes = mem_bytes + b"\x00" * (4 - (len(mem_bytes) % 4))
    with open(path, "w") as f:
        for i in range(0, len(mem_bytes), 4):
            w = mem_bytes[i:i+4]
            val = int.from_bytes(w, "little")
            f.write(f"{val:08x}\n")

def write_trusted_pubkey_h(path, xy64: bytes):
    assert len(xy64) == 64
    with open(path, "w") as f:
        f.write("// Auto-generated by pack_image.py\n#pragma once\n#include <stdint.h>\n\n")
        f.write("static const uint8_t TRUSTED_PUBKEY_XY[64] = {\n")
        for i in range(64):
            f.write(f"0x{xy64[i]:02x},")
            if (i+1) % 16 == 0:
                f.write("\n")
        f.write("};\n")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--rom_ext_bin", required=True)
    ap.add_argument("--bl0_bin", required=True)
    ap.add_argument("--priv_pem", required=True)
    ap.add_argument("--pub_pem", required=True)
    ap.add_argument("--out_hex", default="d_sram.hex")
    ap.add_argument("--out_pubkey_h", default="trusted_pubkey.h")
    args = ap.parse_args()

    rom_ext_payload = open(args.rom_ext_bin, "rb").read()
    bl0_payload     = open(args.bl0_bin, "rb").read()

    # Build container images (copy-to-exec)
    rom_ext_img = build_image(IMG_TYPE_ROM_EXT, rom_ext_payload, EXEC_BASE, EXEC_BASE, args.priv_pem)
    bl0_img     = build_image(IMG_TYPE_BL0,     bl0_payload,     BL0_ENTRY_BASE, BL0_ENTRY_BASE, args.priv_pem)

    # Place into D-SRAM image
    mem = bytearray(b"\x00" * DATA_SRAM_SIZE)

    def place(abs_addr, blob, name):
        off = abs_addr - DATA_SRAM_BASE
        if off < 0 or off + len(blob) > DATA_SRAM_SIZE:
            raise ValueError(f"{name} does not fit: addr=0x{abs_addr:x} off=0x{off:x} len=0x{len(blob):x}")
        mem[off:off+len(blob)] = blob

    place(BOOT_IMG_BASE, rom_ext_img, "ROM_EXT image")
    place(BL0_IMG_BASE,  bl0_img,     "BL0 image")

    write_memh_words_le(args.out_hex, bytes(mem))

    # Generate trusted public key header
    xy64 = extract_pubkey_xy_from_pem(args.pub_pem)
    write_trusted_pubkey_h(args.out_pubkey_h, xy64)

    print(f"Wrote: {args.out_hex}")
    print(f"Wrote: {args.out_pubkey_h}")
    print(f"ROM_EXT image size: {len(rom_ext_img)} bytes @ 0x{BOOT_IMG_BASE:x}")
    print(f"BL0     image size: {len(bl0_img)} bytes @ 0x{BL0_IMG_BASE:x}")

if __name__ == "__main__":
    main()
