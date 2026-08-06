// smoke_puf_boot.S -- new file.
//
// Minimal RV32IM smoke-test program for top_pd_puf's GLS harness. Sibling of
// ../gls/smoke_boot.S (which only proves IMEM fetch + UART for the older
// top_pd), extended to also exercise the two things that distinguish
// top_pd_puf: real ESRAM (write + readback) and the PUF path (trigger
// sample, poll done, read back response word 0). Deliberately still avoids
// DMEM entirely -- that's the memory with the real capacity problem (see
// the DMEM-sizing discussion this file is a direct response to); this
// smoke test sidesteps it rather than trying to fit the full secure-boot
// payload/signature flow into 256 words.
//
// Address map (tl_tlul_2to5_pkg.sv): ROM=0x00000, ESRAM=0x10000,
// DMEM=0x20000 (unused here), UART=0x30000, PUF=0x40000.
// PUF register map (sram_puf_regif.sv): 0x00 CTRL/STATUS (write bit0=1 to
// trigger, read bit0=done), 0x04 DATA0 (first 32 bits of the 512-bit
// response).
//
// UART register offsets/values match test_sw/c/utils/uart.c exactly, same
// as smoke_boot.S: CTRL=+0x10, STATUS=+0x14 (bit0=TXFULL), WDATA=+0x1c,
// NCO=0x2F30 (10MHz -> 115200 baud).
//
// Output: "E" (or lowercase "e" if the ESRAM readback mismatched) then "P"
// once the PUF FSM reports done, then the PUF's first response word as 8
// hex characters, then "!". A capital "EP" followed by 8 hex digits and "!"
// is the expected pass string, e.g. "EP3A9F21C4!" (exact hex value depends
// on the PUF SRAM's preloaded/reset content, not fixed).
.section .text
.globl _start
_start:
    // ---- init UART ----
    li      t0, 0x30010          // UART_CTRL
    li      t1, 0x2F300001       // NCO[31:16] | TX_EN
    sw      t1, 0(t0)

    // ---- ESRAM: write a test pattern, read it back, compare ----
    li      t3, 0x10000          // ESRAM base
    li      t2, 0xdeadbeef
    sw      t2, 0(t3)
    lw      t4, 0(t3)
    li      a0, 'E'
    bne     t4, t2, esram_fail
    jal     print_char
    j       puf_start
esram_fail:
    li      a0, 'e'
    jal     print_char

puf_start:
    // ---- trigger PUF sample ----
    li      t3, 0x40000          // PUF CTRL/STATUS
    li      t2, 1
    sw      t2, 0(t3)

puf_poll:
    lw      t4, 0(t3)
    andi    t4, t4, 1
    beqz    t4, puf_poll

    li      a0, 'P'
    jal     print_char

    // ---- read PUF DATA0 (response[31:0]), print as 8 hex chars ----
    li      t3, 0x40004          // PUF DATA0
    lw      t5, 0(t3)
    li      s1, 8

hex_loop:
    addi    s1, s1, -1
    slli    t6, s1, 2
    srl     a0, t5, t6
    andi    a0, a0, 0xf
    li      t1, 10
    blt     a0, t1, digit
    addi    a0, a0, 55          // 'A' - 10
    j       send_nibble
digit:
    addi    a0, a0, 48          // '0'
send_nibble:
    jal     print_char
    bnez    s1, hex_loop

    li      a0, '!'
    jal     print_char

halt:
    j       halt

// ---- subroutine: print_char(a0) -- busy-waits on UART TXFULL, then writes
// a0. Only touches t0/t1/a0 -- safe to call with t2-t6/s1 live across it. ----
print_char:
    li      t0, 0x30014          // UART_STATUS
wait_txfull:
    lw      t1, 0(t0)
    andi    t1, t1, 1
    bnez    t1, wait_txfull
    li      t0, 0x3001c          // UART_WDATA
    sw      a0, 0(t0)
    ret
