section .multiboot2
align 8
header_start:
    dd 0xE85250D6            ; magic
    dd 0                     ; architecture (i386)
    dd header_end - header_start ; length
	dd -(0xE85250D6 + 0 + (header_end - header_start)) ; checksum

    ; framebuffer request tag
    align 8
    dd 5     ; type
    dd 20    ; size
    dd 0     ; width
    dd 0     ; height
    dd 32    ; depth

    ; end tag
    align 8
    dd 0     ; type
    dd 8     ; size

header_end:

