// top_pd_puf_lui_test_boot.S -- new file.
//
// Same LUI-immediate diagnostic as ibex_lui_bitpattern2_boot.S (5 distinct
// immediates, generously NOP-spaced), but running on REAL top_pd_puf
// hardware through the real IMEM path -- ibex isn't a separable module in
// this flattened netlist, so instead of a testbench BFM this writes to
// real ESRAM (base 0x10000, per tl_tlul_2to5_pkg.sv's address map -- same
// convention smoke_puf_boot.S uses) and the testbench backdoor-reads
// ESRAM's actual storage array afterward. No UART, no PUF touched at all
// -- keeps this test isolated to ibex + xbar + real ESRAM macro, the same
// scope as the standalone ibex_top macro test, but through the actual
// chip-level netlist (and its 4 build stages) instead of the isolated
// macro.
.section .text
.globl _start
_start:
    lui  s0, 0x10        // s0 = 0x00010000 (ESRAM base) -- single LUI,
    nop                   // itself a case worth getting right, hence the
    nop                   // same generous NOP margin as ibex_lui_timing_boot.S's
    nop                   // s0 setup.
    nop
    nop

    lui  t0, 0x00001
    nop
    nop
    nop
    nop
    sw   t0, 0(s0)        // ESRAM+0x0, expect 0x00001000

    lui  t0, 0x00010
    nop
    nop
    nop
    nop
    sw   t0, 4(s0)        // ESRAM+0x4, expect 0x00010000

    lui  t0, 0xfffef
    nop
    nop
    nop
    nop
    sw   t0, 8(s0)        // ESRAM+0x8, expect 0xfffef000

    lui  t0, 0x00000
    nop
    nop
    nop
    nop
    sw   t0, 12(s0)       // ESRAM+0xc, expect 0x00000000

    lui  t0, 0xfffff
    nop
    nop
    nop
    nop
    sw   t0, 16(s0)       // ESRAM+0x10, expect 0xfffff000

    li   t1, 1
    sw   t1, 20(s0)       // ESRAM+0x14, done marker

halt:
    j halt
