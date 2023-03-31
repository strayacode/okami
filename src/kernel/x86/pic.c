#include "kernel/x86/asm.h"
#include "kernel/x86/pic.h"

#define PIC0_COMMAND 0x20
#define PIC0_DATA 0x21
#define PIC1_COMMAND 0xa0
#define PIC1_DATA 0xa1

// commands
#define PIC_EOI 0x20

// pic0 is used for device irqs0-7
// pic1 is used for device irqs8-15

void pic_init(void) {

}

void pic_signal_eoi(uint8_t irq) {
    if (irq < 8) {
        outb(PIC0_COMMAND, PIC_EOI);
    } else {
        outb(PIC1_COMMAND, PIC_EOI);
    }
}