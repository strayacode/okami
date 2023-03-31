#include <stdint.h>
#include "kernel/x86/gdt.h"
#include "kernel/x86/vga.h"

typedef struct __attribute__((packed)) {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_high : 4;
    uint8_t flags : 4;
    uint8_t base_high;
} gdt_entry_t;

typedef struct __attribute__((packed)) {
    uint16_t size;
    uint32_t offset;
} gdt_pointer_t;

extern void gdt_install(void);

gdt_entry_t entries[3];
gdt_pointer_t gdt;

static void gdt_create_entry(int entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    entries[entry].limit_low = limit & 0xffff;
    entries[entry].base_low = base & 0xffff;
    entries[entry].base_mid = (base >> 16) & 0xff;
    entries[entry].access = access;
    entries[entry].limit_high = (limit >> 16) & 0xf;
    entries[entry].flags = flags & 0xf;
    entries[entry].base_high = (base >> 24) & 0xff;
}

// initialise the gdt with proper mappings. there's no guarantee that the gdt used by the
// bootloader is valid for our purposes, so we recreate the mappings
void gdt_init(void)
{
    // null descriptor
    gdt_create_entry(0, 0, 0, 0, 0);
    
    // code descriptor
    gdt_create_entry(1, 0, 0xfffff, 0x9a, 0xc);

    // data descriptor
    gdt_create_entry(2, 0, 0xfffff, 0x92, 0xc);

    // TODO: add tss descriptor when we require hardware task switching
    gdt.size = sizeof(entries) - 1;
    gdt.offset = (uint32_t)&entries;

    gdt_install();
}