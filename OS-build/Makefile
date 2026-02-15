all: build
.PHONY: all build clean


# Source discovery
kernel_source_files := $(shell find source/impl/kernel -name *.c)
kernel_object_files := $(patsubst source/impl/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find source/impl/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst source/impl/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find source/impl/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst source/impl/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)


# Compile kernel C
$(kernel_object_files): build/kernel/%.o : source/impl/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I source/colours -ffreestanding $(patsubst build/kernel/%.o, source/impl/kernel/%.c, $@) -o $@


# Compile x86_64 C
$(x86_64_c_object_files): build/x86_64/%.o : source/impl/x86_64/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I source/colours -ffreestanding $(patsubst build/x86_64/%.o, source/impl/x86_64/%.c, $@) -o $@



# Compile ASM
$(x86_64_asm_object_files): build/x86_64/%.o : source/impl/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, source/impl/x86_64/%.asm, $@) -o $@


	# Build
build: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p distribution-x86_64 && \
	x86_64-elf-ld -n -o distribution-x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp distribution-x86_64/kernel.bin targets/x86_64/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o distribution-x86_64/kernel.iso targets/x86_64
	rm -rf build


# Clean
clean:
	rm -rf build distribution-x86_64
