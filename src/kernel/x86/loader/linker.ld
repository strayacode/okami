ENTRY(_start)

SECTIONS {
    . = 0x7c00;
    .text ALIGN(0x1000): {
        *(.boot)
        *(.text)
    }
    .data ALIGN(0x1000): {
        *(.data)
        *(.rodata)
    }
    .bss ALIGN(0x1000): {
        *(COMMON)
        *(.bss)
    }
}