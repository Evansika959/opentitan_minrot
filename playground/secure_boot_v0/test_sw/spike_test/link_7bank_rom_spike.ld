/* link_7bank_rom_spike.ld -- spike-only ROM linker script. Same structure
 * as link_7bank_rom.ld (everything in one IMEM-shaped region, no DMEM
 * dependency for ROM's own footprint), just based at 0x80000000 to avoid
 * spike's own boot-trampoline device at [0, 0x1000). */
ENTRY(_start)

MEMORY {
  /* Spike-only budget is deliberately larger than the real 0x1C00 (7168B)
   * IMEM hardware capacity -- this build exists to validate the crypto
   * LOGIC fast, not to prove it fits the real chip's memory (that's what
   * the real link_7bank_rom.ld / GLS build is for, separately). */
  IMEM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x4000
  DMEM (rw)  : ORIGIN = 0x80020000, LENGTH = 0x1C00
  PUFM (rw)  : ORIGIN = 0x80040004, LENGTH = 0x20
}

SECTIONS {
  .text 0x80000080 : {
    *(.text.start)
    *(.text*)
  } > IMEM

  .rodata : { *(.rodata*) *(.srodata*) } > IMEM
  .data : { *(.data*) *(.sdata*) } > IMEM
  .bss (NOLOAD) : {
    _bss_start = .;
    *(.bss*) *(.sbss*) *(COMMON)
    _bss_end = .;
  } > IMEM
  .stack (NOLOAD) : { } > IMEM

  /* KEEP() is required here: nothing in the C code references these
   * sections by symbol (they're raw .incbin data, not called functions),
   * so --gc-sections silently discards them otherwise -- exactly what
   * happened on the first attempt (readelf showed no LOAD segment
   * covering either preload region at all, despite no build error). */
  .dmem_preload_sec : { KEEP(*(.dmem_preload_sec)) } > DMEM
  .puf_preload_sec  : { KEEP(*(.puf_preload_sec)) }  > PUFM

  _stack_top = ORIGIN(IMEM) + LENGTH(IMEM) - 0x80;
}
