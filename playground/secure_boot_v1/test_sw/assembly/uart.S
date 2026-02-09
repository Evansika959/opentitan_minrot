    .section .text.start
    .globl _start
    _start:
    # ---- UART base and regs ----
    lui  t0, 0x30          # UART_BASE high (0x0003_0000)
    addi t0, t0, 0         # full base = 0x0003_0000
    li   t1, 0x00000010
    add  t2, t0, t1            # t2 = UART_CTRL addr
    li   t1, 0x00000014
    add  t3, t0, t1            # t3 = UART_STATUS addr
    li   t1, 0x0000001C
    add  t4, t0, t1            # t4 = UART_WDATA addr

    # ---- Configure UART: enable TX + set NCO for 10MHz -> 115200 ----
    # NCO = round(115200 * 2^20 / 10_000_000) = 12080 = 0x2F30
    li   t5, (0x2F30 << 16)    # NCO in [31:16]
    ori  t5, t5, 0x1           # TX_EN
    sw   t5, 0(t2)             # write UART_CTRL

wait_tx_space:
    lw   t6, 0(t3)             # read UART_STATUS
    andi t6, t6, 0x1           # TXFULL? (bit0)
    bnez t6, wait_tx_space     # if full, wait

    li   t5, 0x73              # 's'
    sw   t5, 0(t4)             # write UART_WDATA (byte in [7:0])

hang:
    j    hang
