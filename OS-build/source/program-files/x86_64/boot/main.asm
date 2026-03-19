global start
global stack_top
extern long_start

section .text
bits 32

;waht runs to star with
start:
    mov esp, stack_top

    call check_mb
    call check_cpu
    call check_long

    call build_tables
    call enable_pg

    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_start

    hlt


;cpu check
check_cpu:
    pushfd
    pop eax
    mov ebx, eax

    xor eax, 1 << 21
    push eax
    popfd

    pushfd
    pop eax
    push ebx
    popfd

    cmp eax, ebx
    je .fail
    ret
.fail:
    mov al, "C"
    jmp error


;mutiboot cheker
check_mb:
    cmp eax, 0x36d76289
    jne .fail
    ret
.fail:
    mov al, "M"
    jmp error


;looooong mode
check_long:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .fail

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .fail
    ret
.fail:
    mov al, "L"
    jmp error


;gdt page table builder
build_tables:
    mov eax, pagel3
    or eax, 3
    mov [pagel4], eax

    mov eax, pagel2
    or eax, 3
    mov [pagel3], eax

    xor ebx, ebx

.loop:
    mov eax, ebx
    shl eax, 21
    or eax, 0x83

    mov [pagel2 + ebx*8], eax

    inc ebx
    cmp ebx, 512
    jne .loop

    ret


;enabler of gdt tables (naughtly shouldn't enable people)
enable_pg:
    mov eax, pagel4
    mov cr3, eax

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret


;error messages!!!
error:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte  [0xb800a], al
    hlt


;pages beeing made
section .bss
align 4096
pagel4: resb 4096
pagel3: resb 4096
pagel2: resb 4096

stack_but:  resb 4096 * 4
stack_top:


;gdt tables ^_^
section .rodata
gdt64:
    dq 0
.code_segment: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)
.pointer:
    dw $ - gdt64 - 1
    dq gdt64
