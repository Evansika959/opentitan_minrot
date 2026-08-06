/* link_spike_probe.ld -- timing-probe-only linker script, links at spike's
 * conventional default RAM base (0x80000000) to avoid colliding with
 * spike's built-in low-address CLINT/PLIC device region. Not used by the
 * real demo -- this is purely for the fast cycle-count measurement.
 */
ENTRY(_start)

MEMORY {
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x100000
}

SECTIONS {
  .text 0x80000080 : {
    *(.text.start)
    *(.text*)
  } > RAM

  .rodata : { *(.rodata*) *(.srodata*) } > RAM
  .data : { *(.data*) *(.sdata*) } > RAM
  .bss (NOLOAD) : {
    _bss_start = .;
    *(.bss*) *(.sbss*) *(COMMON)
    _bss_end = .;
  } > RAM
  .stack (NOLOAD) : { } > RAM

  _stack_top = ORIGIN(RAM) + LENGTH(RAM) - 0x80;
}
