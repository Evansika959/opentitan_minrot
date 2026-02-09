#!/usr/bin/env python3
"""
Replace the first 1024 lines of a hex file with the contents of rom.dmem.hex,
padding with zeros if needed.

Usage:
  python replace_dmem.py --source hex/rom.dmem.hex --target hex/rom_with_image.dmem.hex --output hex/rom_with_image.dmem.hex

If --output is omitted and --in-place is not used, the target is overwritten.
"""

import argparse
from pathlib import Path

def load_lines(path: Path) -> list[str]:
    with path.open("r") as f:
        return [line.rstrip("\n\r") for line in f]

def write_lines(path: Path, lines: list[str]) -> None:
    with path.open("w") as f:
        for line in lines:
            f.write(line + "\n")

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", required=True, help="Path to rom.dmem.hex source")
    parser.add_argument("--target", required=True, help="Path to rom_with_image.dmem.hex target")
    parser.add_argument("--output", help="Output path (defaults to target if omitted)")
    parser.add_argument("--in-place", action="store_true", help="Overwrite target in place")
    args = parser.parse_args()

    src_path = Path(args.source)
    tgt_path = Path(args.target)
    out_path = Path(args.output) if args.output else tgt_path
    if args.output and args.in_place:
        parser.error("Use either --output or --in-place, not both")

    src_lines = load_lines(src_path)
    tgt_lines = load_lines(tgt_path)

    # Ensure target has at least 1024 lines for replacement; extend with zeros if shorter.
    zero_line = "00000000"
    if len(tgt_lines) < 1024:
        tgt_lines.extend([zero_line] * (1024 - len(tgt_lines)))

    # Replace the first 1024 lines with src, padding with zeros if src is shorter.
    for i in range(1024):
        if i < len(src_lines):
            line = src_lines[i].strip()
            tgt_lines[i] = line if line else zero_line
        else:
            tgt_lines[i] = zero_line

    write_lines(out_path, tgt_lines)

if __name__ == "__main__":
    main()
