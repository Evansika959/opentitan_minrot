/* link_payload_7bank_spike.ld -- spike-only BL0 linker script, EXEC_BASE
 * shifted to 0x80010000 matching secure_boot_7bank_layout_spike.h. */
ENTRY(payload_main)
SECTIONS
{
  . = 0x80010000;
  .text : { *(.text*) }
  .rodata : { *(.rodata*) *(.srodata*) }
  .bss (NOLOAD) : { *(.bss*) *(.sbss*) *(COMMON) }
  /DISCARD/ : {
    *(.data*) *(.sdata*)
    *(.riscv.attributes) *(.comment) *(.eh_frame)
  }
}
