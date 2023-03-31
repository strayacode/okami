#include <stdint.h>
#include "kernel/x86/interrupts.h"
#include "kernel/x86/idt.h"
#include "kernel/x86/vga.h"

#define NUM_ISRS 256

#define INTERRUPT_GATE 0x8e
#define TRAP_GATE 0x8f

// this is used specifically for syscall interrupts (syscalls should only be called from userland)
#define INTERRUPT_USER_GATE 0xee

typedef struct __attribute__((packed)) {
    uint16_t handler_low;
    uint16_t cs;
    uint8_t reserved;
    uint8_t flags;
    uint16_t handler_high;
} idt_entry_t;

typedef struct __attribute__((packed)) {
    uint16_t size;
    uint32_t offset;
} idtr_t;

extern isr_t isr_table[NUM_ISRS];

__attribute__((aligned(0x10)))
idt_entry_t idt[256];

idtr_t idtr;

void idt_install(void);

static void idt_set_entry(int entry, void *handler, uint8_t flags) {
    idt[entry].handler_low = (uint32_t)handler & 0xffff;
    idt[entry].cs = 0x08;
    idt[entry].reserved = 0;
    idt[entry].flags = flags;
    idt[entry].handler_high = (uint32_t)handler >> 16;
}

void idt_init(void) {
    // initialise the exception entries
    for (int i = 0; i < 32; i++) {
        idt_set_entry(i, isr_table[i], TRAP_GATE);
    }

    // initialise the interrupt entries (can be programmed for other interrupts with the pic)
    for (int i = 32; i < 256; i++) {
        idt_set_entry(i, isr_table[i], INTERRUPT_GATE);
    }

    idtr.size = sizeof(idt) - 1;
    idtr.offset = (uint32_t)&idt;

    idt_install();
}

void idt_install(void) {
    asm volatile(
        "lidt %0;"
        "sti;"
        : : "m"(idtr)
    );
}