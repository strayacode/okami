#include "kernel/x86/idt.h"
#include "kernel/x86/vga.h"
#include "kernel/x86/exceptions.h"

__attribute__((interrupt))
void divide_by_zero_handler(interrupt_frame_t *frame) {
    for (;;) {}
}

void exceptions_init(void) {

}