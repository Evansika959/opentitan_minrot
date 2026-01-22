.section .text
.globl _start
_start:
  # DMEM base = 0x1000_0000
  lui   t0, 0x10000        # t0 = 0x1000_0000

  li    t1, 0xdeadbeef
  sw    t1, 0(t0)          # store to dmem[0]

  nop
  nop

  lw    t2, 0(t0)          # load back
  bne   t1, t2, fail

pass:
  j pass

fail:
  j fail
