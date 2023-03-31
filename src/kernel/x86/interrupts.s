section .text

%macro isr_no_err 1
global isr_handler%+%1
isr_handler%+%1:
    cli
    push byte 0
    push %1
    jmp common_isr_handler
%endmacro

%macro isr_err 1
global isr_handler%+%1
isr_handler%+%1:
    cli
    push %1
    jmp common_isr_handler
%endmacro

extern fault_handler

common_isr_handler:
    pusha ; push all general purpose registers onto the stack

    push ds
    push es
    push fs
    push gs
    mov ax, 0x10 ; load the kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; supply the argument for our fault handler, which will be the pointer to this register frame
    mov eax, esp
    push eax

    ; invoke the fault handler
    mov eax, fault_handler
    call eax

    ; now pop off the stack
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa

    ; also pop off the error code and interrupt number that was pushed earlier
    add esp, 8

    iret

isr_no_err 0
isr_no_err 1
isr_no_err 2
isr_no_err 3
isr_no_err 4
isr_no_err 5
isr_no_err 6
isr_no_err 7
isr_err 8
isr_no_err 9
isr_err 10
isr_err 11
isr_err 12
isr_err 13
isr_err 14
isr_no_err 15
isr_no_err 16
isr_err 17
isr_no_err 18
isr_no_err 19
isr_no_err 20
isr_no_err 21
isr_no_err 22
isr_no_err 23
isr_no_err 24
isr_no_err 25
isr_no_err 26
isr_no_err 27
isr_no_err 28
isr_no_err 29
isr_err 30
isr_no_err 31

%assign i 32
%rep 224
    isr_no_err i
%assign i i+1
%endrep

section .data
global isr_table
isr_table:
%assign i 0
%rep 256
    dd isr_handler%+i
%assign i i+1
%endrep
