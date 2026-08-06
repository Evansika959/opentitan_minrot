/* link_min_rom.ld -- ROM linker script for the top_pd_min real-crypto
 * secure-boot demo. Forked from link_7bank_rom.ld: same convention
 * (everything -- text/rodata/data/bss/stack -- lives inside IMEM's own
 * budget, DMEM untouched by ROM), only LENGTH changed to match
 * tlul_sram_if_macro_ocd_10bank's real capacity: 10 banks x 1KiB = 10KiB.
 */
ENTRY(_start)

MEMORY {
  IMEM (rwx) : ORIGIN = 0x00000000, LENGTH = 0x2800
}

SECTIONS {
  .text 0x80 : {
    *(.text.start)
    *(.text*)
  } > IMEM

  .rodata : {
    *(.rodata*)
    *(.srodata*)
  } > IMEM

  .data : {
    *(.data*)
    *(.sdata*)
  } > IMEM

  .bss (NOLOAD) : {
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(COMMON)
    _bss_end = .;
  } > IMEM

  .stack (NOLOAD) : {
  } > IMEM

  _stack_top = ORIGIN(IMEM) + LENGTH(IMEM) - 0x80;
}
