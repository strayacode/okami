#include <stddef.h>
#include "kernel/kstdio.h"
#include "kernel/x86/interrupts.h"
#include "kernel/x86/pic.h"

#define NUM_EXCEPTIONS 32
#define NUM_IRQS 16

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

// these are for pic interrupts
static isr_t irq_table[NUM_IRQS];

void exception_handler(register_frame_t *registers) {
    kprintf("processor exception occured: %s exception\n", exception_names[registers->interrupt_number]);
    kprintf("halting system...\n");
    
    asm volatile(
        "cli;"
        "hlt;"
    );
}

void irq_handler(register_frame_t *registers) {
    kprintf("pic irq\n");
    isr_t handler = irq_table[registers->interrupt_number - 32];
    if (handler) {
        handler(registers);
    }

    pic_signal_eoi(registers->interrupt_number - 32);
}

void undefined_handler(register_frame_t *registers) {
    kprintf("undefined interrupt occured: %d\n", registers->interrupt_number);
    kprintf("halting system...\n");
    
    asm volatile(
        "cli;"
        "hlt;"
    );
}

void fault_handler(register_frame_t *registers) {
    if (registers->interrupt_number < 32) {
        exception_handler(registers);
    } else if (registers->interrupt_number >= 32 && registers->interrupt_number < 48) {
        irq_handler(registers);
    } else {
        undefined_handler(registers);
    }
}

void install_irq_handler(int index, isr_t handler) {
    irq_table[index] = handler;
}

void uninstall_irq_handler(int index) {
    irq_table[index] = NULL;
}