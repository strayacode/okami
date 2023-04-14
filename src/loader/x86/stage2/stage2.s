_start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov si, stage2_str
    call print_string
    jmp $

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

stage2_str db 'Entered stage2', 0