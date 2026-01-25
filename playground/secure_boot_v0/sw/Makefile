# Makefile (minimal) — builds ROM_EXT + BL0 payloads linked to EXEC_BASE
# and packs signed images into a D-SRAM init hex for Verilator.
#
# Assumes:
#   - riscv32-unknown-elf-* toolchain in PATH
#   - OpenSSL in PATH
#   - micro-ecc vendored at: third_party/micro-ecc/uECC.c uECC.h
#   - sources in: sw/boot/
#
# Layout constants (must match your ROM/ROM_EXT code)
#   EXEC_BASE     = 0x00010000
#   BOOT_IMG_BASE = 0x00021000
#   BL0_IMG_BASE  = 0x00023000
#   DATA_SRAM_BASE= 0x00020000 (size 64KB)

# ---- Toolchain ----
CC       := riscv32-unknown-elf-gcc
OBJCOPY  := riscv32-unknown-elf-objcopy
OBJDUMP  := riscv32-unknown-elf-objdump
SIZE     := riscv32-unknown-elf-size
PY       := python3
OPENSSL  := openssl

# ---- Paths ----
BOOTDIR  := boot
TPDIR    := crypto
UECCDIR  := $(TPDIR)/micro-ecc
TOOLSDIR := tools

# ---- Inputs ----
LINKER   := $(BOOTDIR)/linker.ld
ROM_EXT_C:= $(BOOTDIR)/rom_ext.c
BL0_C    := $(BOOTDIR)/bl0.c
# If you have a tiny crt0 that sets SP and jumps to _start, add it here:
CRT0_S   := $(BOOTDIR)/crt0.S

UECC_C   := $(UECCDIR)/uECC.c
UECC_H   := $(UECCDIR)/uECC.h

PACK_PY  := $(TOOLSDIR)/pack_image.py

# ---- Outputs ----
BUILD    := build
ROM_EXT_ELF := $(BUILD)/rom_ext.elf
BL0_ELF     := $(BUILD)/bl0.elf
ROM_EXT_BIN := $(BUILD)/rom_ext.bin
BL0_BIN     := $(BUILD)/bl0.bin

PRIV_PEM := $(BUILD)/priv.pem
PUB_PEM  := $(BUILD)/pub.pem

DSRAM_HEX := $(BUILD)/d_sram.hex
PUBKEY_H  := $(BOOTDIR)/trusted_pubkey.h  # generated into sw/boot/ for easy include

# ---- Flags ----
CFLAGS_COMMON := -march=rv32imc -mabi=ilp32 \
  -ffreestanding -nostdlib -nostartfiles \
  -fno-builtin -fdata-sections -ffunction-sections \
  -Os -g3 \
  -I$(BOOTDIR) -I$(UECCDIR)

LDFLAGS_COMMON := -T$(LINKER) -Wl,--gc-sections -Wl,-Map,$@.map

# You can enable/disable micro-ecc optimizations here if needed:
# CFLAGS_COMMON += -DuECC_OPTIMIZATION_LEVEL=2

# ---- Default target ----
.PHONY: all
all: $(DSRAM_HEX)

# ---- Build ROM_EXT ----
$(ROM_EXT_ELF): $(ROM_EXT_C) $(LINKER) $(UECC_C) $(UECC_H) $(PUBKEY_H) | $(BUILD)
	$(CC) $(CFLAGS_COMMON) $(LDFLAGS_COMMON) \
	  $(CRT0_S) $(ROM_EXT_C) $(UECC_C) \
	  -o $@
	$(SIZE) $@

$(ROM_EXT_BIN): $(ROM_EXT_ELF) | $(BUILD)
	$(OBJCOPY) -O binary $< $@
	@ls -l $@

# ---- Build BL0 (no uECC needed) ----
$(BL0_ELF): $(BL0_C) $(LINKER) | $(BUILD)
	$(CC) $(CFLAGS_COMMON) $(LDFLAGS_COMMON) \
	  $(CRT0_S) $(BL0_C) \
	  -o $@
	$(SIZE) $@

$(BL0_BIN): $(BL0_ELF) | $(BUILD)
	$(OBJCOPY) -O binary $< $@
	@ls -l $@

# ---- Keys ----
$(PRIV_PEM) $(PUB_PEM): | $(BUILD)
	$(OPENSSL) ecparam -name prime256v1 -genkey -noout -out $(PRIV_PEM)
	$(OPENSSL) ec -in $(PRIV_PEM) -pubout -out $(PUB_PEM)

# ---- Generate trusted_pubkey.h + pack signed images into D-SRAM hex ----
$(DSRAM_HEX): $(ROM_EXT_BIN) $(BL0_BIN) $(PACK_PY) $(PRIV_PEM) $(PUB_PEM) | $(BUILD)
	$(PY) $(PACK_PY) \
	  --rom_ext_bin $(ROM_EXT_BIN) \
	  --bl0_bin $(BL0_BIN) \
	  --priv_pem $(PRIV_PEM) \
	  --pub_pem $(PUB_PEM) \
	  --out_hex $(DSRAM_HEX) \
	  --out_pubkey_h $(PUBKEY_H)
	@echo "DSRAM init hex: $(DSRAM_HEX)"
	@echo "Trusted pubkey header: $(PUBKEY_H)"

# ---- Convenience ----
.PHONY: dump
dump: $(ROM_EXT_ELF) $(BL0_ELF)
	$(OBJDUMP) -d $(ROM_EXT_ELF) | less
	$(OBJDUMP) -d $(BL0_ELF) | less

.PHONY: clean
clean:
	rm -rf $(BUILD) $(PUBKEY_H)

$(BUILD):
	mkdir -p $(BUILD)

# Notes:
# 1) You must provide crt0.S if your environment doesn't set SP before _start.
#    Minimal crt0.S (rv32):
#      .section .text.start
#      .globl _start
#      _start:
#        la sp, _stack_top
#        call _start_c   # or call _start if your C entry is _start
#
# 2) Replace UART stubs in rom_ext.c/bl0.c with your working MMIO UART code.
# 3) Point your Verilator Data SRAM init to: build/d_sram.hex
