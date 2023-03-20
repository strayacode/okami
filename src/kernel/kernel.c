#include <stddef.h>
#include <stdint.h>
#include "kernel/x86/vga.h"

void kmain(void)
{
    // initialise vga text mode
    // this allows us to display characters into a 80x25 grid
    vga_init();

    vga_print("yugenos startup\n");
}