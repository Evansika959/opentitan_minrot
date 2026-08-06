// smoke_boot.S
//
// Minimal RV32IM smoke-test program for the top_pd GLS harness. Deliberately
// tiny (well under the hardened SRAM macro's 256-word / 1 KiB capacity) --
// unlike the real secure_boot_v0 firmware (44 KB IMEM / 64 KB DMEM image,
// see run_gls.bash's findings), this exists only to prove the GLS mechanism
// itself (netlist boots, UART pins toggle correctly, backdoor SRAM preload
// works) independent of the firmware-size question.
//
// No stack, no function calls, no data-memory access at all: the program
// lives entirely in u_imem (the "ROM" hard macro) and never touches u_dmem,
// so run_gls_smoke.bash doesn't need a DMEM image at all.
//
// UART register offsets/values match the real driver exactly
// (test_sw/c/utils/uart.c / uart.h), just inlined here in raw asm:
//   UART_BASE=0x30000, CTRL=+0x10, STATUS=+0x14, WDATA=+0x1c
//   CTRL init = (0x2F30 << 16) | 0x1   (NCO for 10MHz -> 115200 baud, TX_EN)
//   STATUS bit0 = TXFULL
//
// Prints "GLS!" over UART then loops forever.
.section .text
.globl _start
_start:
    li      t0, 0x30010          // UART_CTRL
    li      t1, 0x2F300001       // NCO[31:16] | TX_EN
    sw      t1, 0(t0)

    li      t0, 0x30014          // UART_STATUS
    li      s0, 0x3001c          // UART_WDATA

    li      t2, 'G'
1:  lw      t1, 0(t0)
    andi    t1, t1, 1
    bnez    t1, 1b
    sw      t2, 0(s0)

    li      t2, 'L'
2:  lw      t1, 0(t0)
    andi    t1, t1, 1
    bnez    t1, 2b
    sw      t2, 0(s0)

    li      t2, 'S'
3:  lw      t1, 0(t0)
    andi    t1, t1, 1
    bnez    t1, 3b
    sw      t2, 0(s0)

    li      t2, '!'
4:  lw      t1, 0(t0)
    andi    t1, t1, 1
    bnez    t1, 4b
    sw      t2, 0(s0)

halt:
    j       halt
