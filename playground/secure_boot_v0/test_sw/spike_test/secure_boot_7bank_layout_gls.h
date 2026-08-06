// secure_boot_7bank_layout_gls.h -- shared address/size constants for the
// top_pd_7bank real-crypto secure-boot demo. Included by BOTH the on-target
// ROM C code and the host-side packing tool so the two can never silently
// disagree on where the signed image lives (that class of bug -- ROM
// expecting the image at one DMEM offset while the packer wrote it at a
// different offset -- is exactly what was found, unresolved, in the
// earlier top_pd_puf attempt's rom_puf_secure_boot.c / host_pack_puf_image.c
// pair).
//
// Sizes below reflect top_pd_min (the active target -- IMEM=10bank/10KiB,
// ESRAM/DMEM=2bank/2KiB each), not top_pd_7bank's original uniform 7KiB
// macros this file was first written for -- the address MAP is identical
// between the two (only macro sizes differ), so this file still applies to
// both, and rom_secure_boot_7bank.c/host_pack_7bank_image.c stay unedited
// and shared between them. Tightening these bounds only makes the
// in_range_len() checks stricter, never wrong: the packed container
// (~256B) and payload (149B) are both a small fraction of even the 2KiB
// budget, so top_pd_7bank's own real 7KiB macro is unaffected in practice.
// ROM's own .rodata/.data/.bss/.stack live entirely inside IMEM's own
// budget (see link_min_rom.ld / link_7bank_rom.ld), never touching
// DMEM, so DMEM is reserved 100% for the packed signed container starting
// at word 0.
#pragma once

#define SB7_IMEM_BASE   0x00000000u
#define SB7_IMEM_SIZE   0x00002800u   // 2560 words (10 KiB), top_pd_min real macro capacity

#define SB7_EXEC_BASE   0x00010000u   // ESRAM -- verified payload copied+executed here
#define SB7_EXEC_SIZE   0x00000800u   // 512 words (2 KiB), top_pd_min real macro capacity

#define SB7_DMEM_BASE   0x00020000u   // DMEM -- untrusted staging for the signed container
#define SB7_DMEM_SIZE   0x00000800u   // 512 words (2 KiB), top_pd_min real macro capacity

#define SB7_UART_BASE   0x00030000u
#define SB7_PUF_BASE    0x00040000u

// Packed image starts at word 0 of DMEM -- no reserve needed (ROM's own
// footprint never touches DMEM on this chip).
#define SB7_BOOT_IMG_BASE  SB7_DMEM_BASE
