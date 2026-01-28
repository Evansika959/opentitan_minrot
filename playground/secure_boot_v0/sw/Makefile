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
CC       := riscv64-unknown-elf-gcc
OBJCOPY  := riscv64-unknown-elf-objcopy
OBJDUMP  := riscv64-unknown-elf-objdump
SIZE     := riscv64-unknown-elf-size
PY       := python3
OPENSSL  := openssl

# ---- Paths ----
BOOTDIR  := boot
TPDIR    := crypto
UECCDIR  := $(TPDIR)/micro-ecc
TOOLSDIR := tools

# ---- Inputs ----
LINKER   := $(BOOTDIR)/linker.ld
ROM_LINKER := $(BOOTDIR)/rom_linker.ld
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
PUBKEY_H  := $(BOOTDIR)/trusted_pubkey.h
# generated into sw/boot/ for easy include

ROM_EXT_HEX := $(BUILD)/rom_ext.hex

ROM_ELF   := $(BUILD)/rom.elf
ROM_BIN   := $(BUILD)/rom.bin
IMEM_HEX  := $(BUILD)/imem.hex

# ---- Flags ----
CFLAGS_COMMON := -march=rv32im -mabi=ilp32 \
	-ffreestanding -nostdlib -nostartfiles \
	-fno-builtin -fdata-sections -ffunction-sections \
	-O3 -g \
	-I$(BOOTDIR) -I$(UECCDIR) -Iutils

LDFLAGS_COMMON := -T$(LINKER) -Wl,--gc-sections -Wl,-Map,$@.map

# You can enable/disable micro-ecc optimizations here if needed:
# CFLAGS_COMMON += -DuECC_OPTIMIZATION_LEVEL=2

# ---- Default target ----
.PHONY: all
all: $(DSRAM_HEX)

# Generate trusted_pubkey.h early if you only need the header
.PHONY: pubkey
pubkey: $(PUBKEY_H)

.PHONY: imem
imem: $(IMEM_HEX)

.PHONY: rom_ext_hex
rom_ext_hex: $(ROM_EXT_HEX)

# ---- Build ROM (for IMEM init) ----
ROM_SRCS := $(CRT0_S) $(BOOTDIR)/rom.c $(UECC_C) utils/sha256.c utils/memset.c utils/compat.c utils/uart.c

$(ROM_ELF): $(BOOTDIR)/rom.c $(ROM_LINKER) $(UECC_C) $(UECC_H) $(PUBKEY_H) utils/sha256.c utils/memset.c utils/compat.c utils/uart.c | $(BUILD)
	$(CC) $(CFLAGS_COMMON) -T$(ROM_LINKER) -Wl,--gc-sections -Wl,-Map,$@.map \
	  $(ROM_SRCS) \
	  -o $@
	$(SIZE) $@

$(ROM_BIN): $(ROM_ELF) | $(BUILD)
	$(OBJCOPY) -O binary $< $@
	@ls -l $@

$(IMEM_HEX): $(ROM_BIN) | $(BUILD)
	$(PY) -c "from pathlib import Path; data=Path('$(ROM_BIN)').read_bytes(); data=b'\\x00'*0x80+data; pad=(-len(data))%4; data+=b'\\x00'*pad; f=open('$(IMEM_HEX)','w'); [f.write('{:08x}\\n'.format(int.from_bytes(data[i:i+4],'little'))) for i in range(0,len(data),4)]; f.close(); print('IMEM hex: $(IMEM_HEX)')"
# ---- Build ROM_EXT ----

ROM_EXT_SRCS := $(CRT0_S) $(ROM_EXT_C) $(UECC_C) utils/sha256.c utils/memset.c utils/compat.c utils/uart.c

$(ROM_EXT_ELF): $(ROM_EXT_C) $(LINKER) $(UECC_C) $(UECC_H) $(PUBKEY_H) utils/sha256.c utils/memset.c utils/uart.c | $(BUILD)
	$(CC) $(CFLAGS_COMMON) $(LDFLAGS_COMMON) \
	  $(ROM_EXT_SRCS) \
	  -o $@
	$(SIZE) $@

$(ROM_EXT_BIN): $(ROM_EXT_ELF) | $(BUILD)
	$(OBJCOPY) -O binary $< $@
	@ls -l $@

$(ROM_EXT_HEX): $(ROM_EXT_BIN) | $(BUILD)
	$(PY) tools/gen_rom_ext_hex.py --rom-ext-bin $(ROM_EXT_BIN) --out-hex $(ROM_EXT_HEX) --pack-image $(PACK_PY)

# ---- Build BL0 (no uECC needed) ----
BL0_SRCS := $(CRT0_S) $(BL0_C) utils/memset.c utils/compat.c utils/uart.c

$(BL0_ELF): $(BL0_C) $(LINKER) utils/memset.c | $(BUILD)
	$(CC) $(CFLAGS_COMMON) $(LDFLAGS_COMMON) \
	  $(BL0_SRCS) \
	  -o $@
	$(SIZE) $@

$(BL0_BIN): $(BL0_ELF) | $(BUILD)
	$(OBJCOPY) -O binary $< $@
	@ls -l $@

# ---- Keys ----
$(PRIV_PEM) $(PUB_PEM): | $(BUILD)
	$(OPENSSL) ecparam -name prime256v1 -genkey -noout -out $(PRIV_PEM)
	$(OPENSSL) ec -in $(PRIV_PEM) -pubout -out $(PUB_PEM)

$(PUBKEY_H): $(PUB_PEM) $(PACK_PY) | $(BUILD)
	$(PY) -c "import importlib.util, pathlib;\
spec = importlib.util.spec_from_file_location('pack_image', pathlib.Path('$(PACK_PY)'));\
mod = importlib.util.module_from_spec(spec); spec.loader.exec_module(mod);\
xy = mod.extract_pubkey_xy_from_pem('$(PUB_PEM)');\
mod.write_trusted_pubkey_h('$(PUBKEY_H)', xy);\
print('Wrote: $(PUBKEY_H)')"

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
