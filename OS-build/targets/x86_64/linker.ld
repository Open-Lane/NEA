ENTRY(start)

SECTIONS
{
    /* Multiboot header MUST be first */
    .boot :
    {
        KEEP(*(.multiboot2))
    }

    /* Kernel loads at 1MB */
    . = 1M;

    .text :
    {
        *(.text)
    }

    .rodata :
    {
        *(.rodata*)
    }

    .data :
    {
        *(.data*)
    }

    .bss :
    {
        *(COMMON)
        *(.bss*)
    }
}
