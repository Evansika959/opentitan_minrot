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

# Sources (add more .S or .c files under assembly/ if needed)
ASM_SRCS := $(wildcard $(ASM_DIR)/*.S)
C_SRCS   := $(wildcard $(ASM_DIR)/*.c)

TESTS := $(basename $(notdir $(ASM_SRCS) $(C_SRCS)))

# Flags
CFLAGS  ?= -march=rv32im -mabi=ilp32 -nostdlib -g -O0 -Wall -Wextra
LDFLAGS ?= -nostdlib -static

.PHONY: all clean $(TESTS)

all: $(addprefix $(HEX_DIR)/,$(addsuffix .hex,$(TESTS)))

# Convenience: `make <testname>` builds the corresponding hex
$(TESTS): %: $(HEX_DIR)/%.hex
	@echo "Built $<"

# Hex generation
$(HEX_DIR)/%.hex: $(BUILD_DIR)/%.bin | $(HEX_DIR)
	python3 bin2hex32.py $< > $@

# Binary from ELF
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(OBJCOPY) -O binary $< $@

# Link
$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o link.ld | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -T link.ld -o $@ $(BUILD_DIR)/$*.o $(LDLIBS)

# Compile assembly
$(BUILD_DIR)/%.o: $(ASM_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C (if any)
$(BUILD_DIR)/%.o: $(ASM_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

$(HEX_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(HEX_DIR)
