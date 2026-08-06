// ibex_solo_boot.S -- new file.
//
// Minimal RV32IM program for a standalone gate-level ibex_top GLS test.
// No UART, no TL-UL, no real memory macros -- just a trivial testbench-side
// word-addressable memory BFM on the raw instr_*/data_* OBI-style ports.
// Goal: prove the taped-out ibex_top netlist can fetch, execute ALU ops,
// do a store, do a load, and branch on the comparison -- in complete
// isolation from anything TL-UL/xbar/uart-related, since the top_pd_puf
// integration run showed the data bus (u_data2tl.outstanding_q) never
// launches a single transaction, and this isolates whether that's an
// ibex-side problem or something downstream of it.
//
// Pass/fail signaled by WHICH address gets the final store -- the
// testbench watches its own BFM array directly, no UART needed:
//   0x2000 written -> PASS (load read back what was stored)
//   0x3000 written -> FAIL (mismatch)
.section .text
.globl _start
_start:
    li   t0, 0xcafef00d   // magic value
    li   t1, 0x1000       // scratch data address
    sw   t0, 0(t1)
    lw   t2, 0(t1)
    bne  t2, t0, fail

    li   t3, 0x2000       // PASS marker address
    sw   t0, 0(t3)
pass_halt:
    j    pass_halt

fail:
    li   t3, 0x3000       // FAIL marker address
    sw   t2, 0(t3)
fail_halt:
    j    fail_halt
