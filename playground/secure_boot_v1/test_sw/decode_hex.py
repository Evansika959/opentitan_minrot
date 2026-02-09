#!/usr/bin/env python3
"""Tiny RV32I/M disassembler helper.

Give it 32-bit instruction words (hex) and it prints human-readable mnemonics.
Covers RV32I base and M-extension ALU ops commonly seen in small tests.
"""
from __future__ import annotations
import sys
from typing import Iterable


def sign_extend(val: int, bits: int) -> int:
    mask = 1 << (bits - 1)
    return (val ^ mask) - mask


def reg_name(idx: int) -> str:
    return f"x{idx}"


def decode(word: int) -> str:
    opc = word & 0x7F
    rd = (word >> 7) & 0x1F
    funct3 = (word >> 12) & 0x7
    rs1 = (word >> 15) & 0x1F
    rs2 = (word >> 20) & 0x1F
    funct7 = (word >> 25) & 0x7F

    # Immediate formats
    imm_i = sign_extend(word >> 20, 12)
    imm_s = sign_extend(((word >> 25) << 5) | ((word >> 7) & 0x1F), 12)
    imm_b = sign_extend(
        ((word >> 31) << 12)
        | (((word >> 7) & 0x1) << 11)
        | (((word >> 25) & 0x3F) << 5)
        | (((word >> 8) & 0xF) << 1),
        13,
    )
    imm_u = word & 0xFFFFF000
    imm_j = sign_extend(
        ((word >> 31) << 20)
        | (((word >> 21) & 0x3FF) << 1)
        | (((word >> 20) & 0x1) << 11)
        | (((word >> 12) & 0xFF) << 12),
        21,
    )

    # Opcode decode
    if opc == 0x33:  # R-type
        if funct7 == 0x00:
            return {
                0x0: "add",
                0x1: "sll",
                0x2: "slt",
                0x3: "sltu",
                0x4: "xor",
                0x5: "srl",
                0x6: "or",
                0x7: "and",
            }.get(funct3, "unknown") + f" {reg_name(rd)},{reg_name(rs1)},{reg_name(rs2)}"
        if funct7 == 0x20:
            if funct3 == 0x0:
                return f"sub {reg_name(rd)},{reg_name(rs1)},{reg_name(rs2)}"
            if funct3 == 0x5:
                return f"sra {reg_name(rd)},{reg_name(rs1)},{reg_name(rs2)}"
        if funct7 == 0x01:  # M extension
            m_ops = {
                0x0: "mul",
                0x1: "mulh",
                0x2: "mulhsu",
                0x3: "mulhu",
                0x4: "div",
                0x5: "divu",
                0x6: "rem",
                0x7: "remu",
            }
            if funct3 in m_ops:
                return f"{m_ops[funct3]} {reg_name(rd)},{reg_name(rs1)},{reg_name(rs2)}"

    elif opc == 0x13:  # I-type ALU
        if funct3 == 0x0:
            return f"addi {reg_name(rd)},{reg_name(rs1)},{imm_i}"
        if funct3 == 0x2:
            return f"slti {reg_name(rd)},{reg_name(rs1)},{imm_i}"
        if funct3 == 0x3:
            return f"sltiu {reg_name(rd)},{reg_name(rs1)},{imm_i}"
        if funct3 == 0x4:
            return f"xori {reg_name(rd)},{reg_name(rs1)},{imm_i}"
        if funct3 == 0x6:
            return f"ori {reg_name(rd)},{reg_name(rs1)},{imm_i}"
        if funct3 == 0x7:
            return f"andi {reg_name(rd)},{reg_name(rs1)},{imm_i}"
        if funct3 == 0x1 and funct7 == 0x00:
            shamt = (word >> 20) & 0x1F
            return f"slli {reg_name(rd)},{reg_name(rs1)},{shamt}"
        if funct3 == 0x5:
            shamt = (word >> 20) & 0x1F
            if funct7 == 0x00:
                return f"srli {reg_name(rd)},{reg_name(rs1)},{shamt}"
            if funct7 == 0x20:
                return f"srai {reg_name(rd)},{reg_name(rs1)},{shamt}"

    elif opc == 0x03:  # Loads
        load_ops = {
            0x0: "lb",
            0x1: "lh",
            0x2: "lw",
            0x4: "lbu",
            0x5: "lhu",
        }
        if funct3 in load_ops:
            return f"{load_ops[funct3]} {reg_name(rd)},{imm_i}({reg_name(rs1)})"

    elif opc == 0x23:  # Stores
        store_ops = {0x0: "sb", 0x1: "sh", 0x2: "sw"}
        if funct3 in store_ops:
            return f"{store_ops[funct3]} {reg_name(rs2)},{imm_s}({reg_name(rs1)})"

    elif opc == 0x63:  # Branches
        br_ops = {
            0x0: "beq",
            0x1: "bne",
            0x4: "blt",
            0x5: "bge",
            0x6: "bltu",
            0x7: "bgeu",
        }
        if funct3 in br_ops:
            return f"{br_ops[funct3]} {reg_name(rs1)},{reg_name(rs2)},{imm_b}"

    elif opc == 0x6F:  # JAL
        return f"jal {reg_name(rd)},{imm_j}"

    elif opc == 0x67 and funct3 == 0x0:  # JALR
        return f"jalr {reg_name(rd)},{imm_i}({reg_name(rs1)})"

    elif opc == 0x37:  # LUI
        return f"lui {reg_name(rd)},{imm_u:#x}"

    elif opc == 0x17:  # AUIPC
        return f"auipc {reg_name(rd)},{imm_u:#x}"

    elif opc == 0x0F:  # FENCE / FENCE.I
        if funct3 == 0x0:
            return "fence"
        if funct3 == 0x1:
            return "fence.i"

    elif opc == 0x73:  # SYSTEM / CSR
        if funct3 == 0x0:
            if imm_i == 0:
                return "ecall"
            if imm_i == 1:
                return "ebreak"
            return f"system imm={imm_i}"
        csr = imm_i & 0xFFF
        csr_ops = {
            0x1: "csrrw",
            0x2: "csrrs",
            0x3: "csrrc",
            0x5: "csrrwi",
            0x6: "csrrsi",
            0x7: "csrrci",
        }
        if funct3 in csr_ops:
            if funct3 >= 0x5:
                zimm = rs1  # in immediate CSR ops, rs1 encodes zimm
                return f"{csr_ops[funct3]} {reg_name(rd)},{csr:#x},{zimm}"
            return f"{csr_ops[funct3]} {reg_name(rd)},{csr:#x},{reg_name(rs1)}"

    return f"unknown 0x{word:08x}"


def decode_stream(words: Iterable[int]) -> None:
    for w in words:
        print(f"0x{w:08x}  {decode(w)}")


def parse_words(tokens: Iterable[str]) -> Iterable[int]:
    for t in tokens:
        t = t.strip()
        if not t:
            continue
        base = 16 if t.startswith("0x") else 16
        yield int(t, base)


def main(argv: list[str]) -> int:
    if argv:
        words = list(parse_words(argv))
        decode_stream(words)
        return 0
    words: list[int] = []
    for line in sys.stdin:
        # split on whitespace to allow multiple per line
        for tok in line.strip().replace(",", " ").split():
            if tok:
                words.append(int(tok, 16))
    decode_stream(words)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
