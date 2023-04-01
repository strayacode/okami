#include <stddef.h>
#include <stdint.h>
#include "kernel/kstdio.h"
#include "kernel/x86/vga.h"
#include "kernel/x86/gdt.h"
#include "kernel/x86/pic.h"
#include "kernel/x86/idt.h"
#include "kernel/x86/pit.h"
#include "kernel/x86/timer.h"
#include "kernel/x86/asm.h"

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

    pit_init();
    kprintf("pit initialised\n");

    timer_init();
    kprintf("timer initialised\n");

    kprintf("initialisation finished\n");

    // initialisation is done, so we can enable interrupts now
    sti();

    // TODO: have other processes that will run (e.g. the scheduler)
    // for now we just busy wait at the end, since we should never return from the kernel

    while (1) {}
}