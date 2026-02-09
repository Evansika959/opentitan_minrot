.section .text
.globl _start
_start:
  li   x1, 0x12345678
1: j    1b
