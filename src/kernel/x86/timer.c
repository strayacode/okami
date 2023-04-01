#include "kernel/kstdio.h"
#include "kernel/x86/interrupts.h"
#include "kernel/x86/timer.h"

void timer_callback(register_frame_t *registers) {
    // kprintf("TICK");
}

void timer_init(void) {
    install_irq_handler(0, timer_callback);
}