/* smoke.ld -- minimal linker script for the GLS smoke-test program.
 * Places .text at address 0 of the ELF; run_gls_smoke.bash then extracts
 * just .text and prepends the 0x80-byte reset-vector gap itself (same
 * convention test_sw's build already uses for the real firmware). */
ENTRY(_start)
SECTIONS
{
  . = 0x0;
  .text : { *(.text*) }
  /DISCARD/ : { *(.riscv.attributes) *(.comment) *(.eh_frame) }
}
