ENTRY(_start)

/* Memory map matches the TL-UL xbar:
 * IMEM/ROM at 0x0000_0000 (exec/ro)
 * DMEM SRAM at 0x0002_0000 (rw stack/data)
 */
MEMORY {
  IMEM (rx) : ORIGIN = 0x00000000, LENGTH = 64K
  DMEM (rw) : ORIGIN = 0x00020000, LENGTH = 64K
}

SECTIONS {
  /* Ibex reset vector is at 0x80; place .text there. */
  . = ORIGIN(IMEM) + 0x80;

  /* Code in IMEM */
  .text : {
    *(.text.start)
    *(.text*)
    *(.rodata*)
    *(.srodata*)
  } > IMEM

  /* Read-only data in DMEM (accessible via data bus) */
  .rodata : {
    
  } > DMEM

  /* Initialized data (none currently) lives in DMEM */
  .data : {
    *(.data*)
    *(.sdata*)
  } > DMEM

  /* Zero-initialized data in DMEM */
  .bss (NOLOAD) : {
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(COMMON)
    _bss_end = .;
  } > DMEM

  /* Reserve stack at top of DMEM */
  .stack (NOLOAD) : {
  } > DMEM

  /* Provide a symbol for the stack top.
   * Note: the reset PC is at 0x80 and `la sp, _stack_top` uses PC-relative
   * AUIPC/ADDI. Subtract 0x80 here so AUIPC+PC lands at the true DMEM top. */
  _stack_top = ORIGIN(DMEM) + LENGTH(DMEM) - 0x80;
}
