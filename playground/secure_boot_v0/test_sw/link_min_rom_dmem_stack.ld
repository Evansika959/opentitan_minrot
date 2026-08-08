/* link_min_rom_dmem_stack.ld -- variant of link_min_rom.ld that moves the
 * stack out of IMEM and into DMEM.
 *
 * Why: link_min_rom.ld packs .text/.rodata/.data/.bss/.stack ALL into the
 * same 10KiB IMEM region, with the stack starting near the top and growing
 * downward toward the program's own code/constants. Measured headroom
 * between them was only 312 bytes -- and the crypto call chain
 * (uECC_compute_public_key -> EccPoint_mult -> XYcZ_add/XYcZ_addC ->
 * uECC_vli_modMult_fast -> uECC_vli_mmod, each with their own 24-48 byte
 * local arrays for curve-point coordinates) plausibly needs more than
 * that at peak depth. A stack overflow there would silently overwrite the
 * program's own .rodata (where UART print strings live) and .text -- a
 * real, if unconfirmed, candidate for the corrupted output seen on the
 * one debug build that ran long enough to reach it.
 *
 * Fix: DMEM has 2KiB that's completely idle until the ROM reads the signed
 * container (long after the crypto math's peak stack usage), and even
 * then the container only occupies the first ~256 bytes. Putting the
 * stack at the top of DMEM, growing down, leaves ~1.75KiB of clean margin
 * from the container -- comfortably more than the ~300-800B worst-case
 * stack estimate.
 *
 * The stack pointer setup in crt0.S (la sp, _stack_top) uses PC-relative
 * (AUIPC-based) addressing, which resolves correctly to any target within
 * +-2GB of the PC -- DMEM is only ~128KB from IMEM, so no crt0.S change
 * is needed.
 */
ENTRY(_start)

MEMORY {
  IMEM (rwx) : ORIGIN = 0x00000000, LENGTH = 0x2800
  DMEM (rw)  : ORIGIN = 0x00020000, LENGTH = 0x800
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
  } > DMEM

  _stack_top = ORIGIN(DMEM) + LENGTH(DMEM) - 0x80;
}
