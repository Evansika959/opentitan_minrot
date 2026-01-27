/* rom_linker.ld: link ROM at 0x00000000 (64KB), separate from EXEC SRAM (0x10000) */
OUTPUT_ARCH(riscv)
ENTRY(_start)

ROM_BASE  = 0x00000080;  /* reset vector at 0x80, keep 0x80 gap */
ROM_SIZE  = 0x00010000;

DATA_SRAM_BASE = 0x00020000;
IMG_BASE_MIN   = 0x00021000;  /* start of image storage in D-SRAM */
STACK_TOP      = 0x00010000;  /* end of ROM address space */

MEMORY {
  ROM (rxw) : ORIGIN = ROM_BASE, LENGTH = ROM_SIZE
}

SECTIONS
{
  . = ROM_BASE;

  .text : {
    KEEP(*(.text.start))
    *(.text .text.*)
  } > ROM

  .rodata : { *(.rodata .rodata.*) } > ROM
  .data :  { *(.data .data.*) } > ROM
  .bss  :  {
    PROVIDE(_bss_start = .);
    *(.bss .bss.*) *(COMMON)
    PROVIDE(_bss_end = .);
  } > ROM

  PROVIDE(_stack_top = STACK_TOP);
}
