; declare multiboot header
; align all boot modules on 4kb page boundaries
PAGE_ALIGN equ 1

; get memory information
MEM_INFO equ 1 << 1

; get video information
VIDEO_INFO equ 1 << 2

; flags
FLAGS equ PAGE_ALIGN | MEM_INFO | VIDEO_INFO

; multiboot magic number
MAGIC equ 0x1BADB002

; checksum of multiboot header
CHECKSUM equ -(MAGIC + FLAGS)

; declare the multiboot header in the multiboot section
section .multiboot:
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

dd 0x00000000 ; header_addr
dd 0x00000000 ; load_addr
dd 0x00000000 ; load_end_addr
dd 0x00000000 ; bss_end_addr
dd 0x00000000 ; entry_addr
dd 0x00000000 ; mode_type
dd 640 ; width
dd 480 ; height
dd 32 ; depth


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

    push eax
    push ebx
    call kmain

    ; place the computer into an infinite loop
    cli

loop:
    ; halt until an interrupt happens, this will put the cpu into a more
    ; power efficient state
    hlt
    jmp loop

global gdt_install
extern gdtr
gdt_install:
    cli
    lgdt [gdtr]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:gdt_install2 ; far jump to the code segment
    
gdt_install2:
    ret