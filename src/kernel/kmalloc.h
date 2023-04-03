#ifndef KMALLOC_H
#define KMALLOC_H

#include <stddef.h>

void kmalloc_init(void);
void *kmalloc(size_t size);

#endif