; declare multiboot header
; align all boot modules on 4kb page boundaries
PAGE_ALIGN equ 1

; get memory information
MEM_INFO equ 1 << 1

; flags
FLAGS equ PAGE_ALIGN | MEM_INFO

; multiboot magic number
MAGIC equ 0x1BADB002

; checksum of multiboot header
CHECKSUM equ -(MAGIC + FLAGS)

; declare the multiboot header in the multiboot section
section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

; allocate a small 16kb stack with a bss section
; this allows the object file to be smaller, as the stack
; doesn't need to be initialised
; the stack must also be 16-byte aligned
section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global _start
_start:
    ; make the stack pointer point to the top of the stack
    mov esp, stack_top

    ; call into our c code for the kernel
    extern kmain
    ; call kmain

    mov ebx, 0xb8000
    mov eax, ( 4 << 8 | 0x41)
    mov [ebx], eax

    ; place the computer into an infinite loop
    cli

loop:
    ; halt until an interrupt happens, this will put the cpu into a more
    ; power efficient state
    hlt
    jmp loop