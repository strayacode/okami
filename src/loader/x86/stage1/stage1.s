section .text
bits 16
global _start
_start:
    ; disable external interrupts
    cli

    ; initialise the segment registers to 0
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; save the disk number
    mov [disk], dl

    ; initialise the direction flag
    cld

    ; clear the screen
    mov ax, 0x3
    int 0x10

    ; setup the stack to start right below the bootsector
    ; 0x500-0x7c00 is considered conventional memory in x86
    ; so we can use that
    mov sp, 0x7c00
    mov bp, sp

    mov si, real_mode_str
    call print_string

    mov bx, 0x7e00
    mov dh, 2
    mov dl, [disk]
    call load_stage2

    mov si, disk_success_str
    call print_string

    jmp 0x0000:0x7e00
    
load_stage2:
    pusha
    push dx
    mov ah, 0x2 ; service for reading sectors
    mov al, dh ; number of sectors
    mov ch, 0x0 ; track number
    mov cl, 0x2 ; sector number
    mov dh, 0x0 ; head number
    int 0x13
    jc disk_read_error

    pop dx
    cmp al, dh
    jne disk_sectors_error
    popa
    ret

disk_read_error:
    mov si, disk_read_error_str
    call print_string
    jmp loop

disk_sectors_error:
    mov si, disk_sectors_error_str
    call print_string
    jmp loop

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
    ; print \r\n
    mov al, 0xd
    int 0x10
    mov al, 0xa
    int 0x10
    ret

disk_success_str db 'Successfully read disk', 0
disk_read_error_str db 'Failed to read disk', 0
disk_sectors_error_str db 'Incorrect amount of sectors read', 0
real_mode_str db 'Starting in 16-bit real mode...', 0

times 510 - ($ - $$) db 0
dw 0xaa55