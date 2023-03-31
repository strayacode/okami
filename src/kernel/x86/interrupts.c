#include "kernel/x86/idt.h"
#include "kernel/x86/vga.h"
#include "kernel/x86/interrupts.h"

#define NUM_EXCEPTIONS

static const char *exception_names[NUM_EXCEPTIONS] = {
    "Division by Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

__attribute__((interrupt))
void divide_by_zero_handler(interrupt_frame_t *frame) {
    for (;;) {}
}

void interrupts_init(void) {

}