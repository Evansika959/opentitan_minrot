## Simple RISC-V build for Ibex playground
# Usage examples:
#   make start        # builds hex/start.hex from assembly/start.S
#   make all          # builds hex for every test in assembly/
#   make clean        # removes build/ and hex/

# Toolchain (auto-detect if not provided)
ifeq ($(origin RISCV_PREFIX), undefined)
RISCV_PREFIX := $(shell command -v riscv32-unknown-elf-gcc >/dev/null 2>&1 && echo riscv32-unknown-elf-)
ifeq ($(RISCV_PREFIX),)
RISCV_PREFIX := $(shell command -v riscv64-unknown-elf-gcc >/dev/null 2>&1 && echo riscv64-unknown-elf-)
endif
endif
RISCV_PREFIX ?= riscv32-unknown-elf-
CC      := $(RISCV_PREFIX)gcc
OBJCOPY := $(RISCV_PREFIX)objcopy

# Directories
BUILD_DIR ?= build
HEX_DIR   ?= hex
ASM_DIR   ?= assembly
C_DIR     ?= c

CRT0_OBJ := $(BUILD_DIR)/crt0.o

# Sources (add more .S or .c files under assembly/ and c/)
ASM_SRCS := $(wildcard $(ASM_DIR)/*.S)
C_SRCS   := $(wildcard $(C_DIR)/*.c)
TESTS    := $(basename $(notdir $(ASM_SRCS) $(C_SRCS)))

# Flags
# Use the toolchain's standard headers (e.g. stdint.h) instead of providing local copies.
STDINCDIR    := $(shell $(CC) -print-file-name=include)
PICOLIBC_DIR ?= /usr/lib/picolibc/riscv64-unknown-elf
CFLAGS  ?= -march=rv32im -mabi=ilp32 -nostdlib -g -O0 -Wall -Wextra
CFLAGS  += -isystem $(STDINCDIR) -isystem $(PICOLIBC_DIR)/include
LDFLAGS ?= -nostdlib -static

.PHONY: all clean $(TESTS)

all: \
	$(addprefix $(HEX_DIR)/,$(addsuffix .hex,$(TESTS))) \
	$(addprefix $(HEX_DIR)/,$(addsuffix .imem.hex,$(TESTS))) \
	$(addprefix $(HEX_DIR)/,$(addsuffix .dmem.hex,$(TESTS)))

# Convenience: `make <testname>` builds the corresponding hex
$(TESTS): %: $(HEX_DIR)/%.hex $(HEX_DIR)/%.imem.hex $(HEX_DIR)/%.dmem.hex
	@echo "Built $<"

# Hex generation (combined, IMEM-only, DMEM-only)
$(HEX_DIR)/%.hex: $(BUILD_DIR)/%.bin | $(HEX_DIR)
	python3 bin2hex32.py $< > $@

$(HEX_DIR)/%.imem.hex: $(BUILD_DIR)/%.imem.bin | $(HEX_DIR)
	python3 bin2hex32.py $< > $@

$(HEX_DIR)/%.dmem.hex: $(BUILD_DIR)/%.dmem.bin | $(HEX_DIR)
	python3 bin2hex32.py $< > $@

# Disassemble an IMEM hex using the local decoder (optional helper).
$(HEX_DIR)/%.imem.disasm: $(HEX_DIR)/%.imem.hex decode_hex.py | $(HEX_DIR)
	python3 decode_hex.py < $< > $@

# Binary from ELF (combined, IMEM-only, DMEM-only)
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.imem.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	# Extract text, then prepend 0x80 bytes (reset vector offset) of zeros to keep padding in the flat binary.
	$(OBJCOPY) -O binary \
	  --only-section=.text --only-section=.text.* \
	  $< $@.body
	# Prepend 0x80 bytes of zero padding
	( dd if=/dev/zero bs=1 count=128 of=$@.pad status=none && cat $@.pad $@.body > $@ )
	rm -f $@.pad $@.body

$(BUILD_DIR)/%.dmem.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O binary \
	  --only-section=.rodata --only-section=.rodata.* \
	  --only-section=.srodata --only-section=.srodata.* \
	  --only-section=.data --only-section=.data.* \
	  --only-section=.sdata --only-section=.sdata.* \
	  --change-section-address .rodata-0x20000 --change-section-address .rodata.*-0x20000 \
	  --change-section-address .srodata-0x20000 --change-section-address .srodata.*-0x20000 \
	  --change-section-address .data-0x20000 --change-section-address .data.*-0x20000 \
	  --change-section-address .sdata-0x20000 --change-section-address .sdata.*-0x20000 \
	  $< $@

# Link
$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o $(CRT0_OBJ) link.ld | $(BUILD_DIR)
	@extra_objs=""; \
	if [ -f $(C_DIR)/$*.c ]; then extra_objs="$(CRT0_OBJ)"; fi; \
	$(CC) $(CFLAGS) $(LDFLAGS) -T link.ld -o $@ $$extra_objs $(BUILD_DIR)/$*.o $(LDLIBS)

# Compile assembly
$(BUILD_DIR)/%.o: $(ASM_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C (if any)
$(BUILD_DIR)/%.o: $(C_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# C runtime startup (stack/BSS init)
$(CRT0_OBJ): $(C_DIR)/crt0.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Generate assembly from C (helper target: make <name>.s)
$(BUILD_DIR)/%.s: $(C_DIR)/%.c | $(ASM_DIR)
	$(CC) $(CFLAGS) -S -o $@ $<

# Keep generated assembly outputs (do not delete intermediates)
.PRECIOUS: $(BUILD_DIR)/%.s

# Convenience: phony to emit assembly alongside hex
%.s: $(BUILD_DIR)/%.s
	@echo "Built $<"

$(BUILD_DIR):
	mkdir -p $@

$(HEX_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(HEX_DIR)
