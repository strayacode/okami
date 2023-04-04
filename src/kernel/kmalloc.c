#include "kernel/util.h"
#include "kernel/kstdio.h"
#include "kernel/kmalloc.h"

#define HEAP_SIZE 1 * MB

// this file contains functionality for dynamic allocation
uint32_t heap_base;

void kmalloc_init(uint32_t base) {
    heap_base = align_up(base, 4 * KB);
    kprintf("heap_base: %x\n", heap_base);
}