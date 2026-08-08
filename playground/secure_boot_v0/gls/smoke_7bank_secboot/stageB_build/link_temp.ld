/* link_7bank_rom.ld -- ROM linker script for the top_pd_7bank real-crypto
 * secure-boot demo. Unlike test_sw's generic link.ld (which puts
 * .rodata/.data/.bss/.stack in a separate DMEM region), everything here
 * lives inside IMEM's own 1792-word (7KiB) real-macro budget -- confirmed
 * data-bus-reachable (see secure_boot_7bank_layout.h) -- so ROM never
 * touches DMEM, leaving all of DMEM free for the packed signed container.
 */
ENTRY(_start)

MEMORY {
  IMEM (rwx) : ORIGIN = 0x00000000, LENGTH = 0x4000
}

SECTIONS {
  /* Ibex fetches its first instruction at boot_addr+0x80. */
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

  /* Same PC-relative `la sp, _stack_top` convention as test_sw/link.ld:
   * subtract 0x80 so the AUIPC-relative load lands on the true IMEM top
   * (reset PC is 0x80, not 0). */
  _stack_top = ORIGIN(IMEM) + LENGTH(IMEM) - 0x80;
}
