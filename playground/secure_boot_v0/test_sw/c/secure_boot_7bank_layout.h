// secure_boot_7bank_layout.h -- shared address/size constants for the
// top_pd_7bank real-crypto secure-boot demo. Included by BOTH the on-target
// ROM C code and the host-side packing tool so the two can never silently
// disagree on where the signed image lives (that class of bug -- ROM
// expecting the image at one DMEM offset while the packer wrote it at a
// different offset -- is exactly what was found, unresolved, in the
// earlier top_pd_puf attempt's rom_puf_secure_boot.c / host_pack_puf_image.c
// pair).
//
// top_pd_7bank unifies IMEM/ESRAM/DMEM onto the same tlul_sram_if_macro_
// ocd_7bank macro (7 banks x 1KiB = 7KiB = 1792 words each), confirmed
// directly against rtl/top_pd_7bank.sv's u_imem/u_esram/u_dmem instances --
// unlike top_pd_puf, where DMEM was a separate, much smaller (256-word)
// macro. That means, unlike the top_pd_puf demo, there is no need to fight
// for every word: ROM's own .rodata/.data/.bss/.stack live entirely inside
// IMEM's own 1792-word budget (confirmed data-bus-reachable via xbar_tlul_
// 2to5's dual-host sm1_7 arbitration on d_rom, same mechanism that makes
// ESRAM fetchable-and-writable) instead of borrowing DMEM space, so DMEM is
// reserved 100% for the packed signed container starting at word 0.
#pragma once

#define SB7_IMEM_BASE   0x00000000u
#define SB7_IMEM_SIZE   0x00001C00u   // 1792 words (7 KiB), real macro capacity

#define SB7_EXEC_BASE   0x00010000u   // ESRAM -- verified payload copied+executed here
#define SB7_EXEC_SIZE   0x00001C00u

#define SB7_DMEM_BASE   0x00020000u   // DMEM -- untrusted staging for the signed container
#define SB7_DMEM_SIZE   0x00001C00u

#define SB7_UART_BASE   0x00030000u
#define SB7_PUF_BASE    0x00040000u

// Packed image starts at word 0 of DMEM -- no reserve needed (ROM's own
// footprint never touches DMEM on this chip).
#define SB7_BOOT_IMG_BASE  SB7_DMEM_BASE
