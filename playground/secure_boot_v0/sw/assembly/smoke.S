.section .text
.globl _start
_start:
  # DMEM base = 0x0002ff68
  lui   t0, 0x00030        # 0x00030000
  addi  t0, t0, -152       # -> 0x0002ff68

  li    t1, 0xdeadbeef
  sb    t1, 3(t0)          # store top byte (mask 0x8)

  nop
  nop

  lbu   t2, 3(t0)          # load back byte
  li    t3, 0xde
  bne   t3, t2, fail

pass:
  j pass

fail:
  j fail
