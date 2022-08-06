.section .text
.code16
.global _start
_start:
    /* enable the a20 line */
    mov ax, 0x2401
    int 0x15
    
    /* set vga text mode to safe value */
    mov ax, 0x3
    int 0x10

    /* load sector to support up to 1024 for bootloader */
    mov [disk], dl
    mov ah, 0x2
    mov al, 0x6
    mov ch, 0x0
    mov dh, 0x0
    mov cl, 0x2
    mov dl, [disk]
    mov bx, start_protected_mode
    int 0x13

    /* disable interrupts */
    cli

    /* load the gdt */
    lgdt [gdt]

    /* enable protected mode */
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    /* load rest of segment registers */
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    /* far jump to the code segment */
    jmp 0x08, offset start_protected_mode

gdt_start:
gdt_null_descriptor:
    .quad 0x0

gdt_code_descriptor:
    .word 0xffff
    .word 0x0
    .byte 0x0
    .byte 0x9a
    .byte 0xcf
    .byte 0x0

gdt_data_descriptor:
    .word 0xffff
    .word 0x0
    .byte 0x0
    .byte 0x92
    .byte 0xcf
    .byte 0x0

gdt_end:
gdt:
    .word gdt_end - gdt_start
    .long gdt_start

disk:
    .byte 0x0

.set CODE_SEG, gdt_code_descriptor - gdt_start
.set DATA_SEG, gdt_data_descriptor - gdt_start

.fill (510-(. - _start)), 1, 0
.word 0xaa55

.code32
start_protected_mode:
    mov stack_top, esp
    
    call kernel_main

    cli

1:
    hlt
    jmp 1b

.section bss
.align 16
stack_bottom:
.skip 16384
stack_top: