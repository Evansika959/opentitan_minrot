#!/usr/bin/env python3

"""
Overlay a pre-compiled boot image (hex words) into rom.dmem.hex.

Usage: python3 load_image.py <rom.dmem.hex> <boot_image.hex> <out.hex>

Assumptions:
- Hex files are 32-bit little-endian words, one per line (bin2hex32.py format).
- DATA SRAM base is 0x20000, boot image base is 0x21000.
"""

import sys
from pathlib import Path

DMEM_BASE = 0x00020000
BOOT_IMG_BASE = 0x00021000  # must live in D-SRAM
WORD_SIZE = 4


def read_words(path: Path):
	with path.open() as f:
		return [int(line.strip(), 16) for line in f if line.strip()]


def write_words(path: Path, words):
	with path.open("w") as f:
		for w in words:
			f.write(f"{w:08x}\n")


def main():
	if len(sys.argv) != 4:
		print("Usage: python3 load_image.py <rom.dmem.hex> <boot_image.hex> <out.hex>")
		sys.exit(1)

	rom_path = Path(sys.argv[1])
	img_path = Path(sys.argv[2])
	out_path = Path(sys.argv[3])

	rom_words = read_words(rom_path)
	img_words = read_words(img_path)

	offset_bytes = BOOT_IMG_BASE - DMEM_BASE
	if offset_bytes % WORD_SIZE != 0:
		raise ValueError("BOOT_IMG_BASE not word-aligned relative to DMEM_BASE")

	start = offset_bytes // WORD_SIZE
	end = start + len(img_words)

	if end > len(rom_words):
		rom_words.extend([0] * (end - len(rom_words)))

	rom_words[start:end] = img_words

	write_words(out_path, rom_words)


if __name__ == "__main__":
	main()
