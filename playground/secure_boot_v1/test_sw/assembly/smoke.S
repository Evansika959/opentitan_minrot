.section .text
.globl _start
_start:
  lui   t0, 0x00020        # 0x00020000
  addi  t0, t0, 0x153       # -> 0x00020150

  li    t1, 0xdeadbeef
  sb    t1, 2(t0)          # store top byte (mask 0x8)

  nop
  nop

  lbu   t2, 2(t0)          # load back byte
  li    t3, 0xef
  bne   t3, t2, fail

pass:
  j pass

fail:
  j fail
