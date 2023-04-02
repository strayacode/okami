#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "kernel/kstdio.h"
#include "kernel/multiboot.h"
#include "kernel/x86/vga.h"
#include "kernel/x86/gdt.h"
#include "kernel/x86/pic.h"
#include "kernel/x86/idt.h"
#include "kernel/x86/pit.h"
#include "kernel/x86/timer.h"
#include "kernel/x86/asm.h"

static bool boot_mbi1(multiboot_info_t *multiboot_ptr) {
    if (!(multiboot_ptr->flags & 0x1)) {
        kprintf("lower and upper memory not available\n");
        return false;
    }

    kprintf("lower memory size: %x\n", multiboot_ptr->mem_lower);
    kprintf("upper memory size: %x\n", multiboot_ptr->mem_upper);

    if (!((multiboot_ptr->flags >> 6) & 0x1)) {
        kprintf("invalid memory map supplied\n");
        return false;
    }

    kprintf("mmap address: %x\n", multiboot_ptr->mmap_addr);
    kprintf("mmap length: %x\n", multiboot_ptr->mmap_length);

    for (uint32_t i = 0; i < multiboot_ptr->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
        multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t *)(multiboot_ptr->mmap_addr + i);

        switch (entry->type) {
        case 1:
            kprintf("mmap entry: start %x%x | length %x%x | size %x | free\n", entry->base_high, entry->base_low, entry->length_high, entry->length_low, entry->size);
            break;
        case 2:
            kprintf("mmap entry: start %x%x | length %x%x | size %x | reserved\n", entry->base_high, entry->base_low, entry->length_high, entry->length_low, entry->size);
            break;
        default:
            kprintf("mmap entry: start %x%x | length %x%x | size %x | unimplemented\n", entry->base_high, entry->base_low, entry->length_high, entry->length_low, entry->size);
            break;
        }
        
    }

    if (!((multiboot_ptr->flags >> 12) & 0x1)) {
        kprintf("framebuffer support not available\n");
    } else {
        kprintf("framebuffer address: %x\n", multiboot_ptr->framebuffer_addr);
        kprintf("framebuffer pitch: %d\n", multiboot_ptr->framebuffer_pitch);
        kprintf("framebuffer width: %d\n", multiboot_ptr->framebuffer_width);
        kprintf("framebuffer height: %d\n", multiboot_ptr->framebuffer_height);
        kprintf("framebuffer bpp: %d\n", multiboot_ptr->framebuffer_bpp);
        kprintf("framebuffer type: %d\n", multiboot_ptr->framebuffer_type);
    }

    return true;
}

void kmain(multiboot_info_t *multiboot_ptr, uint32_t magic) {
    vga_init();
    kprintf("okami startup...\n");
    kprintf("vga initialised\n");

    bool result = false;
    if (magic == MULTIBOOT1_MAGIC) {
        result = boot_mbi1(multiboot_ptr);
    } else {
        kprintf("bootloader is not multiboot compliant\n");
        return;
    }

    if (!result) {
        kprintf("multiboot init sequence failed\n");
        return;
    }

    gdt_init();
    kprintf("gdt initialised\n");

    pic_init();
    kprintf("pic initialised\n");

    idt_init();
    kprintf("idt initialised\n");

    timer_init();
    kprintf("timer initialised\n");

    pit_init();
    kprintf("pit initialised\n");

    kprintf("initialisation finished\n");

    // initialisation is done, so we can enable interrupts now
    sti();

    // TODO: have other processes that will run (e.g. the scheduler)
    // for now we just busy wait at the end, since we should never return from the kernel

    while (1) {}
}