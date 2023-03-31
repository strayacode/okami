#include <stddef.h>
#include <stdint.h>
#include "kernel/kstdio.h"
#include "kernel/x86/vga.h"
#include "kernel/x86/gdt.h"
#include "kernel/x86/pic.h"
#include "kernel/x86/idt.h"
#include "kernel/x86/interrupts.h"

void kmain(void) {
    vga_init();
    kprintf("okami startup...\n");
    kprintf("vga initialised\n");

    gdt_init();
    kprintf("gdt initialised\n");

    pic_init();
    kprintf("pic initialised\n");

    idt_init();
    kprintf("idt initialised\n");

    interrupts_init();
}