// ibex_lui_timing_boot.S -- new file.
//
// Isolates whether the LUI anomaly seen in ibex_top_solo_gls_tb.sv is a
// pure logic defect (LUI computes the wrong value, period) or a timing/
// hazard issue (LUI's result needs N cycles before it's safely readable,
// and something that should stall/forward for that isn't). Re-does the
// same `lui t0, 0xcafef` five times, each followed by a different number
// of NOPs (0..4) before storing t0 -- if some delay makes the stored value
// correct (0xcafef000) where 0-delay was wrong, that's a timing/hazard
// bug; if it's wrong at every delay, LUI's computation itself is wrong.
//
// s0 is established ONCE as the base pointer (0x2000), with a 5-NOP safety
// margin after its own lui and an independent sanity check (stored to
// address 0, which needs no register at all) BEFORE being trusted as a
// base for the five delay cases -- avoids the same immediate-use-after-lui
// hazard confounding the address computation itself.
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

    // ---- delay=0 ----
    lui  t0, 0xcafef
    sw   t0, 0(s0)      // address 0x2000

    // ---- delay=1 ----
    lui  t0, 0xcafef
    nop
    sw   t0, 4(s0)      // address 0x2004

    // ---- delay=2 ----
    lui  t0, 0xcafef
    nop
    nop
    sw   t0, 8(s0)      // address 0x2008

    // ---- delay=3 ----
    lui  t0, 0xcafef
    nop
    nop
    nop
    sw   t0, 12(s0)     // address 0x200c

    // ---- delay=4 ----
    lui  t0, 0xcafef
    nop
    nop
    nop
    nop
    sw   t0, 16(s0)     // address 0x2010

    li   t1, 1
    sw   t1, 20(s0)     // address 0x2014, done marker

halt:
    j halt
