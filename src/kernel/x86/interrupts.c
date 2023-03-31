#include "kernel/kstdio.h"
#include "kernel/x86/interrupts.h"

#define NUM_EXCEPTIONS 32

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

void fault_handler(register_frame_t *registers) {
    if (registers->interrupt_number < 32) {
        kprintf("processor exception occured: %s exception\n", exception_names[registers->interrupt_number]);
    }
}