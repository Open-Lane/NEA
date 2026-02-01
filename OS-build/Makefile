# ----------------------------
# Compiler / Linker / Assembler
# ----------------------------
CC := x86_64-elf-gcc
LD := x86_64-elf-ld
NASM := nasm

CFLAGS := -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -nostdlib -n

# ----------------------------
# Directories
# ----------------------------
BUILD_DIR := build
DIST_DIR := dist/x86_64

KERNEL_SRC := source/impl/kernel
X86_64_SRC := source/impl/x86_64
BOOT_SRC := $(X86_64_SRC)/boot
ISO_DIR := targets/x86_64/iso

# ----------------------------
# Source files
# ----------------------------
KERNEL_C_SRC := $(shell find $(KERNEL_SRC) -name '*.c')
KERNEL_OBJ   := $(patsubst $(KERNEL_SRC)/%.c,$(BUILD_DIR)/kernel/%.o,$(KERNEL_C_SRC))

X86_64_C_SRC := $(shell find $(X86_64_SRC) -maxdepth 1 -name '*.c')
X86_64_C_OBJ := $(patsubst $(X86_64_SRC)/%.c,$(BUILD_DIR)/x86_64/%.o,$(X86_64_C_SRC))

BOOT_ASM_SRC := $(shell find $(BOOT_SRC)/ -name '*.asm')
BOOT_ASM_OBJ := $(patsubst $(BOOT_SRC)/%.asm,$(BUILD_DIR)/x86_64/boot/%.o,$(BOOT_ASM_SRC))

MULTIBOOT_OBJ := $(BUILD_DIR)/x86_64/boot/header.o
OBJS := $(MULTIBOOT_OBJ) $(filter-out $(MULTIBOOT_OBJ), $(KERNEL_OBJ) $(X86_64_C_OBJ) $(BOOT_ASM_OBJ))

# ----------------------------
# Build
# ----------------------------
all: build-x86_64

build-x86_64: $(OBJS)
	mkdir -p $(DIST_DIR)/boot/grub
	mkdir -p $(ISO_DIR)/boot
	$(LD) $(LDFLAGS) -T targets/x86_64/linker.ld -o $(DIST_DIR)/kernel.bin $(OBJS)
	cp $(DIST_DIR)/kernel.bin $(ISO_DIR)/boot/kernel.bin
	grub-mkrescue -o $(DIST_DIR)/kernel.iso $(ISO_DIR)

# ----------------------------
# Compile rules
# ----------------------------

$(BUILD_DIR)/kernel/%.o: $(KERNEL_SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./source/colours -c $< -o $@

$(BUILD_DIR)/x86_64/%.o: $(X86_64_SRC)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I./source/colours -c $< -o $@

$(BUILD_DIR)/x86_64/boot/%.o: $(BOOT_SRC)/%.asm
	mkdir -p $(dir $@)
	$(NASM) -f elf64 $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)
