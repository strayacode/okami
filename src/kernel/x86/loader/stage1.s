section .boot
bits 16
global _start
_start:
    ; disable interrupts
    cli

    ; initialise the segment registers to 0
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ah, 0xe
    mov al, 'S'
    int 0x10

loop:
    hlt
    jmp loop

times 510 - ($ - $$) db 0
dw 0xaa55
