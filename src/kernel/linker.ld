ENTRY(_start)

SECTIONS {
    . = 0x100000;
    kernel_start = .;
    .text ALIGN(0x1000): {
        *(.multiboot)
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
    kernel_end = .;
}