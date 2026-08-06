/* smoke_puf.ld -- minimal linker script for the top_pd_puf smoke-test
 * program. Same convention as ../gls/smoke.ld: places .text at address 0
 * of the ELF; the build script extracts just .text and prepends the
 * 0x80-byte reset-vector gap itself (Ibex always fetches its first
 * instruction from {boot_addr_i[31:8], 8'h80} -- see ibex_if_stage.sv --
 * regardless of what boot_addr_i's own literal value is). */
ENTRY(_start)
SECTIONS
{
  . = 0x0;
  .text : { *(.text*) }
  /DISCARD/ : { *(.riscv.attributes) *(.comment) *(.eh_frame) }
}
