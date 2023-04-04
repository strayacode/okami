#include <stddef.h>
#include "kernel/kstdio.h"
#include "kernel/pmm.h"

// the bitmap consists of an array of uint32_ts,
// where a bit being set to 1 indicates that it's used,
// and a bit being set to 0 indicates that it's free
static uint32_t *bitmap_base;
static uint32_t ram_size;
static uint32_t max_frames;
static uint32_t used_frames;

void pmm_mark_free(uint32_t frame) {
    bitmap_base[frame / 32] &= ~(1 << (frame % 32));
}

void pmm_mark_used(uint32_t frame) {
    bitmap_base[frame / 32] |= 1 << (frame % 32);
}

void pmm_init_region(paddr_t base, uint32_t length) {
    length = align_up(length, 4 * KB);
    
    size_t num_frames = length / PAGE_SIZE_4K;

    for (int i = 0; i < num_frames; i++) {
        pmm_mark_free((base / PAGE_SIZE_4K) + i);
        used_frames--;
    }

    // frame 0 should always be reserved (for ivt and bda)
    pmm_mark_used(0);
}

void pmm_init_regions(multiboot_info_t *multiboot_ptr) {
    for (uint32_t i = 0; i < multiboot_ptr->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
        multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t *)(multiboot_ptr->mmap_addr + i);

        if (entry->type == 1) {
            pmm_init_region(entry->base_low, entry->length_low);
        }
    }
}

void pmm_init(paddr_t base, multiboot_info_t *multiboot_ptr) {
    bitmap_base = (uint32_t *)align_up(base, PAGE_SIZE_4K);

    for (uint32_t i = 0; i < multiboot_ptr->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
        multiboot_mmap_entry_t *entry = (multiboot_mmap_entry_t *)(multiboot_ptr->mmap_addr + i);
        ram_size = entry->base_low + entry->length_low - 1;
    }

    max_frames = div_ceil(ram_size, PAGE_SIZE_4K);
    used_frames = max_frames;
    pmm_init_regions(multiboot_ptr);

    kprintf("total amount of physical ram: %dkb\n", div_ceil(ram_size, KB));
    kprintf("max frames: %d\n", max_frames);
    kprintf("used frames: %d\n", used_frames);
    kprintf("free frames: %d\n", max_frames - used_frames);
}