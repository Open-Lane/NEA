global long_start
extern the_kernel
extern stack_top

section .text
bits 64
long_start:
    ; set up a clean 64-bit stack
    mov rsp, stack_top

	call the_kernel
    hlt
