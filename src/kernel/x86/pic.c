#include "kernel/kstdio.h"
#include "kernel/x86/asm.h"
#include "kernel/x86/pic.h"

#define PIC0_COMMAND 0x20
#define PIC0_DATA 0x21
#define PIC1_COMMAND 0xa0
#define PIC1_DATA 0xa1

// commands
#define PIC_INIT 0x11
#define PIC_EOI 0x20

// pic0 is used for device irqs0-7
// pic1 is used for device irqs8-15

void pic_init(void) {
    // save the initial pic0 and pic1 masks
    uint8_t pic0_mask = inb(PIC0_DATA);
    uint8_t pic1_mask = inb(PIC1_DATA);

    // send the init command
    outb(PIC0_COMMAND, PIC_INIT);
    iowait();
    outb(PIC1_COMMAND, PIC_INIT);
    iowait();

    // specify the offset of pic irqs to processor irqs
    // pic0 takes up irq32-39
    // pic1 takes up irq40-47
    outb(PIC0_DATA, 32);
    iowait();
    outb(PIC1_DATA, 40);
    iowait();

    // specify how pic0 and pic1 are connected
    // pic1 is connected to irq2 of pic0
    outb(PIC0_DATA, 1 << 2);
    iowait();
    outb(PIC1_DATA, 2);
    iowait();

    // specify that we are using x86
    outb(PIC0_DATA, 1);
    iowait();
    outb(PIC1_DATA, 1);
    iowait();

    // restore the initial pic0 and pic1 masks
    outb(PIC0_DATA, pic0_mask);
    outb(PIC1_DATA, pic1_mask);
}

void pic_signal_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC1_COMMAND, PIC_EOI);
    }

    outb(PIC0_COMMAND, PIC_EOI);
}

void pic_set_mask(uint8_t irq) {
    uint16_t port;
    if (irq < 8) {
        port = PIC0_DATA;
    } else {
        port = PIC1_DATA;
        irq -= 8;
    }

    uint8_t mask = inb(port) | (1 << irq);
    outb(port, mask);
}

void pic_clear_mask(uint8_t irq) {
    uint16_t port;
    if (irq < 8) {
        port = PIC0_DATA;
    } else {
        port = PIC1_DATA;
        irq -= 8;
    }

    uint8_t mask = inb(port) & ~(1 << irq);
    outb(port, mask);
}