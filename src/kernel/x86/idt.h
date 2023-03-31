#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define INTERRUPT_GATE 0x8e
#define TRAP_GATE 0x8f

// this is used specifically for syscall interrupts (syscalls should only be called from userland)
#define INTERRUPT_USER_GATE 0xee

void idt_set_entry(int entry, void *handler, uint8_t flags);
void idt_init(void);

#endif