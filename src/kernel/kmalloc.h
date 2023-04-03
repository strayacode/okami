#ifndef KMALLOC_H
#define KMALLOC_H

#include <stddef.h>
#include <stdint.h>

void kmalloc_init(uint32_t base);
void *kmalloc(size_t size);

#endif