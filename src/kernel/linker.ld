ENTRY(_start)

SECTIONS {
    . = 0x100000;
    .text ALIGN(0x1000): {
        *(.multiboot)
        *(.text)
        *(.rodata)
    }
    .data ALIGN(0x1000): {
        *(.data)
    }
    .bss ALIGN(0x1000): {
        *(COMMON)
        *(.bss)
    }
}