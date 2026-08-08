// ibex_lui_bitpattern2_boot.S -- new file.
//
// Re-run of ibex_lui_bitpattern_boot.S's five-immediate test, but with
// generous NOP spacing (4 cycles after each lui before its store, 3
// cycles after each store before the next lui) so each case is cleanly
// isolated -- the previous attempt packed all five lui+store pairs back
// to back with zero delay, which (combined with the single-outstanding
// memory BFM stalling the LSU between stores) may have let one case's
// pipeline state bleed into the next, muddying the results. Same five
// immediates, same expected values, same s0 sanity-check setup.
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
    nop
    nop
    nop

    lui  t0, 0x00001
    nop
    nop
    nop
    nop
    sw   t0, 0(s0)      // address 0x2000, expect 0x00001000
    nop
    nop
    nop

    lui  t0, 0x00010
    nop
    nop
    nop
    nop
    sw   t0, 4(s0)      // address 0x2004, expect 0x00010000
    nop
    nop
    nop

    lui  t0, 0xfffef
    nop
    nop
    nop
    nop
    sw   t0, 8(s0)      // address 0x2008, expect 0xfffef000
    nop
    nop
    nop

    lui  t0, 0x00000
    nop
    nop
    nop
    nop
    sw   t0, 12(s0)     // address 0x200c, expect 0x00000000
    nop
    nop
    nop

    lui  t0, 0xfffff
    nop
    nop
    nop
    nop
    sw   t0, 16(s0)     // address 0x2010, expect 0xfffff000
    nop
    nop
    nop

    li   t1, 1
    sw   t1, 20(s0)     // address 0x2014, done marker

halt:
    j halt
