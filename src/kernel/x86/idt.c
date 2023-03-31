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

extern void idt_install(void);

void stub_interrupt_handler(void) {
    vga_print("interrupt handler\n");
}

static void idt_create_entry(int entry, uint32_t handler, uint8_t flags) {
    idt[entry].handler_low = handler & 0xffff;
    idt[entry].cs = 0x08;
    idt[entry].reserved = 0;
    idt[entry].flags = flags;
    idt[entry].handler_high = (handler >> 16) & 0xffff;
}

void idt_init(void) {
    for (int i = 0; i < 256; i++) {
        idt_create_entry(i, (uint32_t)&stub_interrupt_handler, 0x8e);
    }

    idtr.size = sizeof(idt) - 1;
    idtr.offset = (uint32_t)&idt;

    idt_install();
}