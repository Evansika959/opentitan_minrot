// ibex_lui_bitpattern_boot.S -- new file.
//
// Distinguishes a true stuck-at fault on LUI-result bit 16 from an
// input-pattern-dependent logic error. Same s0-base-pointer setup as
// ibex_lui_timing_boot.S (5-NOP margin + independent sanity store to
// address 0), but this time varying the LUI IMMEDIATE (not the delay,
// which is already proven irrelevant) across five cases chosen to
// directly exercise immediate-bit-4 (-> result bit 16) both ways:
//   0x00001 -> expect 0x00001000 (bit16 should read 0)
//   0x00010 -> expect 0x00010000 (bit16 should read 1)
//   0xfffef -> expect 0xfffef000 (bit16 should read 0, everything else 1)
//   0x00000 -> expect 0x00000000 (bit16 should read 0, everything else 0)
//   0xfffff -> expect 0xfffff000 (bit16 should read 1, everything else 1)
// If bit16 reads 1 in EVERY case regardless of what it should be, that's
// a stuck-at-1 fault. If it tracks the expected value correctly in some
// cases and not others in a pattern tied to the OTHER immediate bits,
// that's a genuine (not stuck-at) logic error.
.section .text
.globl _start
_start:
    lui  s0, 0x2
    nop
    nop
    nop
    nop
    nop
    sw   s0, 0(x0)      // sanity: address 0 should get 0x00002000

    lui  t0, 0x00001
    sw   t0, 0(s0)      // address 0x2000, expect 0x00001000

    lui  t0, 0x00010
    sw   t0, 4(s0)      // address 0x2004, expect 0x00010000

    lui  t0, 0xfffef
    sw   t0, 8(s0)      // address 0x2008, expect 0xfffef000

    lui  t0, 0x00000
    sw   t0, 12(s0)     // address 0x200c, expect 0x00000000

    lui  t0, 0xfffff
    sw   t0, 16(s0)     // address 0x2010, expect 0xfffff000

    li   t1, 1
    sw   t1, 20(s0)     // address 0x2014, done marker

halt:
    j halt
