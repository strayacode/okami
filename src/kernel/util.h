#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define KB 1024
#define MB KB * KB
#define PAGE_SIZE_4K (4 * KB)

typedef uint32_t addr_t;
typedef addr_t paddr_t;
typedef addr_t vaddr_t;

addr_t align_down(addr_t addr, uint32_t bound);
addr_t align_up(addr_t addr, uint32_t bound);
uint32_t div_ceil(uint32_t value, uint32_t divisor);

#endif