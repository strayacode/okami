#include <stddef.h>
#include <stdint.h>
#include "kernel/x86/vga.h"
#include "kernel/x86/gdt.h"

void kmain(void)
{
    vga_init();
    vga_print("okami startup...\n");
    vga_print("vga initialised\n");

    gdt_init();
    vga_print("gdt initialised\n");
}