section .boot
bits 16
global _start
_start:
    ; disable external interrupts
    cli

    ; save the disk number
    mov [disk], dl

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
    mov ax, 0x7e0
    mov es, ax ; target segment
    mov ah, 0x2 ; service for reading sectors
    mov al, STAGE2_NUM_SECTORS ; number of sectors
    mov ch, 0x0 ; track number
    mov cl, 0x2 ; sector number
    mov dh, 0x0 ; head number
    mov dl, [disk] ; type of disk (floppy = 0x00, hdd = 0x80)
    mov bx, 0x0 ; target offset in segment
    int 0x13
    jc disk_load_error

    jmp 0x7e0:0

disk_load_error:
    mov si, disk_error_str
    call print_string

loop:
    hlt
    jmp loop

STAGE2_NUM_SECTORS equ 1

disk:
    db 0x0

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

disk_error_str db 'Failed to read disk', 0

times 510 - ($ - $$) db 0
dw 0xaa55
