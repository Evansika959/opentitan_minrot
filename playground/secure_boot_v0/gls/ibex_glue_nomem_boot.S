// ibex_glue_nomem_boot.S -- new file.
//
// Minimal program for the glue-with-no-esram bisection test: a single
// LUI into s0, then an infinite loop. Deliberately avoids any store --
// the data-side ibex_to_tlul_host has its tl_i tied to TL_D2H_DEFAULT
// (a_ready=1 always, d_valid=0 always), so a store's write-response would
// never arrive and the LSU would stall forever. Since LUI's register
// writeback happens in ID/EX with no memory access at all, s0 is
// observable via backdoor register-file probe well before that matters.
.section .text
.globl _start
_start:
    lui  s0, 0x2
    nop
    nop
    nop
    nop
    nop
    nop
    nop
halt:
    j halt
