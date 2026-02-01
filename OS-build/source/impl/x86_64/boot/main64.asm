global long_mode_start
extern the_kernel

section .text
bits 64

long_mode_start:
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    mov rsp, stack_top64
    call the_kernel

.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_top64: resb 16384
