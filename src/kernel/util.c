#include "kernel/util.h"

// align an address down to the lower bound
uint32_t align_down(uint32_t addr, uint32_t bound) {
    return addr & ~(bound - 1);
}

uint32_t align_up(uint32_t addr, uint32_t bound) {
    uint32_t amount = bound - (addr & (bound - 1));
    return addr + amount;
}