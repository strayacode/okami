#include "kernel/kstdio.h"
#include "kernel/x86/asm.h"
#include "kernel/x86/pit.h"

#define PIT0_DATA 0x40
#define PIT1_DATA 0x41
#define PIT2_DATA 0x42
#define PIT_COMMAND 0x43

#define PIT_INPUT_CLOCK 1193180

static void pit_configure(int hz) {
    // the has a clock of 1193180hz
    // since we can only store up to a 16-bit value for the divisor,
    // we can't easily do small hz values
    int divisor = PIT_INPUT_CLOCK / hz;
    outb(PIT_COMMAND, 0x36);
    outb(PIT0_DATA, divisor & 0xff);
    outb(PIT0_DATA, (divisor >> 8) & 0xff);
}

void pit_init(void) {
    // tick once per second
    pit_configure(100);
}