#!/usr/bin/env python3
import csv, sys, hashlib
from collections import defaultdict

def load_puf_bits(csv_path, chip_id):
    """Load one chip's PUF response, majority-voting across all Read
    trials for each Bit position to get a stable response vector."""
    votes = defaultdict(list)  # bit_idx -> list of Winner values across reads
    with open(csv_path) as f:
        reader = csv.DictReader(f)
        for row in reader:
            if int(row['Chip']) != chip_id:
                continue
            bit_idx = int(row['Bit'])
            winner = int(row['Winner'])
            votes[bit_idx].append(winner)

    if not votes:
        raise ValueError(f"No data found for chip {chip_id}")

    num_bits = max(votes.keys()) + 1
    bits = []
    for i in range(num_bits):
        reads = votes.get(i, [])
        if not reads:
            raise ValueError(f"Missing bit {i} for chip {chip_id}")
        ones = sum(reads)
        bits.append('1' if ones * 2 > len(reads) else '0')

    return ''.join(bits)

def puf_to_key(bitstring):
    """Derive a 256-bit key from raw PUF bits -- stands in for the
    default_RNG() replacement at platform-specific.inc in the real design."""
    packed = int(bitstring, 2).to_bytes((len(bitstring) + 7) // 8, 'big')
    return hashlib.sha256(packed).digest()

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <csv_path> <chip_id>")
        sys.exit(1)

    csv_path = sys.argv[1]
    chip_id = int(sys.argv[2])

    bits = load_puf_bits(csv_path, chip_id)
    key = puf_to_key(bits)

    print(f"Chip {chip_id} raw PUF response ({len(bits)} bits): {bits}")
    print(f"Derived key (SHA-256): {key.hex()}")
