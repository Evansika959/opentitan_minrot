/* linker.ld (for ROM_EXT and BL0) */
OUTPUT_ARCH(riscv)
ENTRY(_start)

EXEC_BASE  = 0x00010000;
EXEC_SIZE  = 0x00010000;

DATA_SRAM_BASE = 0x00020000;
IMG_BASE_MIN   = 0x00021000;  /* start of image storage in D-SRAM */
STACK_TOP      = 0x00020000;   /* stack grows down from 0x20000 */

MEMORY {
  EXEC (rxw) : ORIGIN = EXEC_BASE, LENGTH = EXEC_SIZE
}

SECTIONS
{
  . = EXEC_BASE;

  .text : {
    KEEP(*(.text.start))
    *(.text .text.*)
  } > EXEC

  .rodata : { *(.rodata .rodata.*) } > EXEC
  .data :  { *(.data .data.*) } > EXEC
  .bss  :  {
    PROVIDE(_bss_start = .);
    *(.bss .bss.*) *(COMMON)
    PROVIDE(_bss_end = .);
  } > EXEC

  PROVIDE(_stack_top = STACK_TOP);
}
