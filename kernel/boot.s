section .boot
bits 16
global _start
_start:
    ; enable the a20 line
    mov ax, 0x2401
    int 0x15
    
    ; set vga text mode to safe value
    mov ax, 0x3
    int 0x10

    ; load sector to support up to 1024 for bootloader
    mov [disk], dl
    mov ah, 0x2
    mov al, 0x6
    mov ch, 0x0
    mov dh, 0x0
    mov cl, 0x2
    mov dl, [disk]
    mov bx, start_protected_mode
    int 0x13

    ; disable interrupts
    cli

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

disk:
    db 0x0

CODE_SEG equ gdt_code_descriptor - gdt_start
DATA_SEG equ gdt_data_descriptor - gdt_start

times 510 - ($ - $$) db 0
dw 0xaa55

bits 32
start_protected_mode:
    mov esp, stack_top
    
    extern kernel_main
    call kernel_main

    cli

loop:
    hlt
    jmp loop

section .bss
align 16
stack_bottom:
    resb 16384
stack_top: