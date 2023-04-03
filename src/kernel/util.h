#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define KB 1024
#define MB KB * KB

uint32_t align_down(uint32_t addr, uint32_t bound);
uint32_t align_up(uint32_t addr, uint32_t bound);

#endif