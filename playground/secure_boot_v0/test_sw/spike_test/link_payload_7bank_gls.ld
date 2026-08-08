/* link_payload_7bank_gls.ld -- links the verified BL0 payload at EXEC_BASE
 * (0x10000 = SB7_EXEC_BASE), which ROM copies it to at runtime after
 * verifying its signature, then jumps into. No crt0/stack setup needed --
 * reached via a plain function-pointer jump from ROM, inheriting ROM's
 * already-initialized stack.
 *
 * Forked from link_payload.ld, which placed .bss at address 0x30000 (the
 * UART's own MMIO address!) -- harmless there only because payload_stage.c
 * has no actual .bss (no static/global variables), so the section ends up
 * empty and the address is never really used. Placed properly inside
 * ESRAM's own budget here instead, since it costs nothing to do so.
 *
 * Originally had no MEMORY region at all -- a payload of any size would
 * link silently, with nothing catching an oversized build until it hit
 * ROM's own runtime bounds check (verify_header()'s in_range_len against
 * SB7_EXEC_SIZE) at actual boot time, on real gates, with a generic
 * "BAD RANGE" die() giving no hint the real cause was payload size. Bound
 * to ESRAM's real 2KiB (0x800) capacity here instead, so an oversized
 * payload fails loudly at build time -- the same class of check
 * link_min_rom.ld already relies on for the ROM's own IMEM budget.
 */
ENTRY(payload_main)

MEMORY {
  ESRAM (rwx) : ORIGIN = 0x00010000, LENGTH = 0x800
}

SECTIONS
{
  .text : { *(.text*) } > ESRAM
  .rodata : { *(.rodata*) *(.srodata*) } > ESRAM

  .bss (NOLOAD) : { *(.bss*) *(.sbss*) *(COMMON) } > ESRAM

  /DISCARD/ : {
    *(.data*) *(.sdata*)
    *(.riscv.attributes) *(.comment) *(.eh_frame)
  }
}
