ENTRY(_start)

SECTIONS {
    . = 0x7c00;
    .text ALIGN(0x1000): {
        *(.text)
    }
    .data ALIGN(0x1000): {
        *(.data)
    }
    .rodata ALIGN(0x1000): {
        *(.rodata)
    }
    .bss ALIGN(0x1000): {
        *(.bss)
    }
}