section .boot
bits 16
global _start
_start:
    ; disable interrupts
    cli

    ; clear the screen
    mov ax, 0x3
    int 0x10

    ; initialise the segment registers to 0
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; setup the stack to start right below the bootsector
    ; 0x500-0x7c00 is considered conventional memory in x86
    ; so we can use that
    mov sp, 0x7c00

load_stage2:
    ; load the stage2 bootloader

    mov si, disk_fail_str
    call print_string

loop:
    hlt
    jmp loop

print_string:
    ; set mode for printing characters
    mov ah, 0xe

print_character:
    ; load next character from si into al
    lodsb

    ; finish printing when we encounter \0
    cmp al, 0
    je print_string_end

    ; print the character and start printing next character
    int 0x10
    jmp print_character

print_string_end:
    ret

disk_fail_str db 'Failed to read disk', 0

times 510 - ($ - $$) db 0
dw 0xaa55
