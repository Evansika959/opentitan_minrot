#!/usr/bin/env python3
"""Generate a ROM_EXT hex file with boot header prepended.

Reads a ROM_EXT payload binary, prefixes a 64-byte boot header, pads to
signature offset, appends a zeroed signature placeholder, aligns to 4 bytes,
and writes one 32-bit little-endian word per line.
"""
import argparse
from pathlib import Path
import importlib.util


def load_pack_image_module(pack_image_path: Path):
    spec = importlib.util.spec_from_file_location('pack_image', pack_image_path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def build_rom_ext_image(payload: bytes, mod):
    payload_off = mod.HDR_LEN
    payload_len = len(payload)
    sig_off = (payload_off + payload_len + 3) & ~3  # 4-byte align
    sig_len = mod.SIG_LEN

    header = mod.make_header_exact(
        mod.IMG_TYPE_ROM_EXT,
        payload_off,
        payload_len,
        mod.EXEC_BASE,
        mod.EXEC_BASE,
        sig_off,
        sig_len,
    )
    pad_len = sig_off - (payload_off + payload_len)
    image = header + payload + (b"\x00" * pad_len) + (b"\x00" * sig_len)
    # align to 4 bytes for word output
    if len(image) % 4:
        image += b"\x00" * (4 - (len(image) % 4))
    return image, payload_off, payload_len, sig_off, sig_len


def write_hex_le(path: Path, blob: bytes):
    with path.open("w") as f:
        for i in range(0, len(blob), 4):
            w = int.from_bytes(blob[i:i+4], "little")
            f.write(f"{w:08x}\n")


def main():
    ap = argparse.ArgumentParser(description="Generate ROM_EXT hex with header")
    ap.add_argument("--rom-ext-bin", required=True, help="Path to rom_ext.bin payload")
    ap.add_argument("--out-hex", required=True, help="Output hex file path")
    ap.add_argument("--pack-image", default="tools/pack_image.py", help="Path to pack_image.py for constants/header builder")
    args = ap.parse_args()

    payload = Path(args.rom_ext_bin).read_bytes()
    mod = load_pack_image_module(Path(args.pack_image))

    image, payload_off, payload_len, sig_off, sig_len = build_rom_ext_image(payload, mod)
    out_path = Path(args.out_hex)
    write_hex_le(out_path, image)

    print(f"ROM_EXT hex with header: {out_path}")
    print(f"Header fields: payload_off={payload_off} payload_len={payload_len} sig_off={sig_off} sig_len={sig_len}")


if __name__ == "__main__":
    main()
