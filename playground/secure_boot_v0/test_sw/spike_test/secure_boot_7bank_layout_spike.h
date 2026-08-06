// secure_boot_7bank_layout_spike.h -- SPIKE-ONLY address map for fast
// algorithm/logic validation of rom_secure_boot_7bank.c + host_pack_
// 7bank_image.c, before running the identical-logic binary on the real
// GLS gates at its true addresses.
//
// Spike reserves [0, 0x1000) for its own default boot trampoline (visible
// in an interactive trace: auipc/csrr mhartid/jr sequence at 0x1000,
// before jumping to the ELF's real entry point) -- a real, unavoidable
// conflict with this design's true IMEM base of 0x0. Rather than fight
// spike's fixed device map, every base here is uniformly shifted up by
// 0x80000000 (spike's conventional flat-RAM base, already used by
// timing_probe.c's link_spike_probe.ld) -- same relative structure
// (IMEM/ESRAM/DMEM/UART/PUF offsets unchanged), just relocated to a
// spike-safe absolute location. All code uses these as symbolic macros,
// never raw hex, so shifting the base uniformly changes nothing about
// the logic being validated -- only where it physically sits.
//
// The real GLS/hardware target keeps using secure_boot_7bank_layout.h
// (true addresses, base 0x0) unchanged -- this header exists only for the
// fast spike correctness pass.
#pragma once

#define SB7_IMEM_BASE   0x80000000u
#define SB7_IMEM_SIZE   0x00001C00u

#define SB7_EXEC_BASE   0x80010000u
#define SB7_EXEC_SIZE   0x00001C00u

#define SB7_DMEM_BASE   0x80020000u
#define SB7_DMEM_SIZE   0x00001C00u

#define SB7_UART_BASE   0x80030000u
#define SB7_PUF_BASE    0x80040000u

#define SB7_BOOT_IMG_BASE  SB7_DMEM_BASE
