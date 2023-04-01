#include "kernel/kstdio.h"
#include "kernel/x86/interrupts.h"
#include "kernel/x86/pic.h"
#include "kernel/x86/timer.h"

int ticks = 0;

void timer_callback(register_frame_t *registers) {
    ticks++;

    if (ticks % 100 == 0) {
        ticks = 0;
        kprintf("TICK");
    }
}

void timer_init(void) {
    // enable timer interrupts with irq0 in pic
    pic_clear_mask(0);

    install_irq_handler(0, timer_callback);
}