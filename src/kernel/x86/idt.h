#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define INTERRUPT_GATE 0x8e
#define TRAP_GATE 0x8f

// this is used specifically for syscall interrupts (syscalls should only be called from userland)
#define INTERRUPT_USER_GATE 0xee

// assume privilege-level change
typedef struct __attribute__((packed)) {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t esp;
    uint32_t ss;
} interrupt_frame_t;

void idt_set_entry(int entry, void *handler, uint8_t flags);
void idt_init(void);


#endif