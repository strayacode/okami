KERNEL_NUM_SECTORS equ 9

section .text
bits 16
_start:
    ; save the disk number
    mov [disk], dl
    pop dx

    ; enable the a20 line
    mov ax, 0x2401
    int 0x15

    mov si, stage2_str
    call print_string

    mov bx, 0x9000
    mov dh, KERNEL_NUM_SECTORS
    mov dl, [disk]
    call load_kernel

    mov si, disk_success_str
    call print_string

    ; load the gdt
    lgdt [gdt]

    ; enable protected mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; load rest of segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; far jump to the code segment
    jmp CODE_SEG:start_protected_mode

    jmp $

load_kernel:
    pusha
    push dx
    mov ah, 0x2 ; service for reading sectors
    mov al, dh ; number of sectors
    mov ch, 0x0 ; track number
    mov cl, 0x3 ; sector number
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
    jmp loop16

disk_sectors_error:
    mov si, disk_sectors_error_str
    call print_string
    jmp loop16

loop16:
    hlt
    jmp loop16

gdt_start:
gdt_null_descriptor:
    dq 0x0

gdt_code_descriptor:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data_descriptor:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:
gdt:
    dw gdt_end - gdt_start
    dd gdt_start

CODE_SEG equ gdt_code_descriptor - gdt_start
DATA_SEG equ gdt_data_descriptor - gdt_start

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

stage2_str db 'Entered stage2', 0
disk_success_str db 'Successfully read disk', 0
disk_read_error_str db 'Failed to read disk', 0
disk_sectors_error_str db 'Incorrect amount of sectors read', 0

bits 32
start_protected_mode:
    mov al, 'C'	; desired character
	mov ah, 0x0f ; black background, white character
    mov [0xb8000], ax

    mov esp, stack_top

    mov al, 'C'	; desired character
	mov ah, 0x0f ; black background, white character
    mov [0xb8001], ax
    
    mov eax, 0x9000
    call eax
    cli

loop32:
    hlt
    jmp loop32

section .bss
align 16
stack_bottom:
    resb 16384
stack_top: