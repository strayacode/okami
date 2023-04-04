#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#include "kernel/util.h"
#include "kernel/multiboot.h"

void pmm_init(paddr_t base, multiboot_info_t *multiboot_ptr);

#endif