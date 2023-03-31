#include "kernel/x86/asm.h"

void outb(uint16_t port, uint8_t data) {
    asm volatile(
        "outb %1, %0;"
        :: "dN"(port), "a"(data)
    );
}

void cli(void) {
    asm volatile("cli;");
}

void sti(void) {
    asm volatile("sti;");
}