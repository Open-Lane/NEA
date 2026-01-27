CC := gcc
LD := ld

KERNEL_SRC_DIR := source/impl/kernel
X86_64_SRC_DIR := source/impl/x86_64
BUILD_DIR := build
DIST_DIR := dist/x86_64

CFLAGS32 := -ffreestanding -fno-pie -fno-stack-protector -O2 -m32

BOOT32_ASM := source/impl/x86_64/boot/main.asm
BOOT32_OBJ := $(BUILD_DIR)/x86_64/boot32.o

# Build C as 32-bit
kernel_source_files := $(shell find $(KERNEL_SRC_DIR) -name '*.c')
kernel_object_files := $(patsubst $(KERNEL_SRC_DIR)/%.c, $(BUILD_DIR)/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find $(X86_64_SRC_DIR) -name '*.c' -not -path '$(X86_64_SRC_DIR)/boot/*')
x86_64_c_object_files := $(patsubst $(X86_64_SRC_DIR)/%.c, $(BUILD_DIR)/x86_64/%.o, $(x86_64_c_source_files))

$(BUILD_DIR)/kernel/%.o: $(KERNEL_SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -I source/intf -I source/colours $(CFLAGS32) $< -o $@

$(BUILD_DIR)/x86_64/%.o: $(X86_64_SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c -I source/intf -I source/colours $(CFLAGS32) $< -o $@

# Boot stub with MB2 header must be elf32
$(BOOT32_OBJ): $(BOOT32_ASM)
	mkdir -p $(dir $@)
	nasm -f elf32 $< -o $@

.PHONY: build-x86_64 clean

# Build an ELF32 kernel GRUB can load (MB2), then you jump to long mode in code
build-x86_64: $(kernel_object_files) $(x86_64_c_object_files) $(BOOT32_OBJ)
	mkdir -p $(DIST_DIR)
	$(LD) -m elf_i386 -nostdlib -n -T targets/x86_64/linker32.ld -o $(DIST_DIR)/kernel.elf \
	$(BOOT32_OBJ) $(x86_64_c_object_files) $(kernel_object_files)
	mkdir -p targets/x86_64/iso/boot targets/x86_64/iso/boot/grub
	cp $(DIST_DIR)/kernel.elf targets/x86_64/iso/boot/kernel.elf
	cp source/impl/grub.cfg targets/x86_64/iso/boot/grub/grub.cfg
	grub-mkrescue -o $(DIST_DIR)/kernel.iso targets/x86_64/iso

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)

