#include <stdint.h>
#include "kernel/x86/idt.h"
#include "kernel/x86/vga.h"

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

__attribute__((aligned(0x10)))
idt_entry_t idt[256];

idtr_t idtr;

void idt_install(void);

__attribute__((interrupt))
void default_exception_handler_no_error(interrupt_frame_t *frame) {
    asm volatile("cli; hlt;");
    for (;;) {}
}

__attribute__((interrupt))
void default_exception_handler_error(interrupt_frame_t *frame, uint32_t error) {
    asm volatile("cli; hlt;");
    for (;;) {}
}

__attribute__((interrupt))
void default_interrupt_handler(interrupt_frame_t *frame) {
    asm volatile("cli; hlt;");
    for (;;) {}
}

void idt_set_entry(int entry, void *handler, uint8_t flags) {
    idt[entry].handler_low = (uint32_t)handler & 0xffff;
    idt[entry].cs = 0x08;
    idt[entry].reserved = 0;
    idt[entry].flags = flags;
    idt[entry].handler_high = (uint32_t)handler >> 16;
}

void idt_init(void) {
    // initialise the exception entries
    for (int i = 0; i < 32; i++) {
        switch (i) {
        case 8: case 10: case 11: case 12: case 13: case 14: case 17: case 30:
            idt_set_entry(i, default_exception_handler_error, TRAP_GATE);
            break;
        default:
            idt_set_entry(i, default_exception_handler_no_error, TRAP_GATE);
            break;
        }
    }

    // initialise the interrupt entries (can be programmed for other interrupts with the pic)
    for (int i = 32; i < 256; i++) {
        idt_set_entry(i, default_interrupt_handler, INTERRUPT_GATE);
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