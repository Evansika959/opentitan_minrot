.section .text.start
.globl _start
_start:
  /* Set stack pointer to top of DMEM (provided by linker) */
  la   sp, _stack_top

  /* Zero .bss */
  la   a0, _bss_start
  la   a1, _bss_end
1:
  beq  a0, a1, 2f
  sw   zero, 0(a0)
  addi a0, a0, 4
  j    1b
2:
  /* Call main */
  call main

  /* If main returns, halt */
3: j 3b

