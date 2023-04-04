#include "kernel/util.h"

// align an address down to the lower bound
addr_t align_down(addr_t addr, uint32_t bound) {
    return addr & ~(bound - 1);
}

addr_t align_up(addr_t addr, uint32_t bound) {
    uint32_t amount = bound - (addr & (bound - 1));
    return addr + amount;
}

uint32_t div_ceil(uint32_t value, uint32_t divisor) {
    return (value / divisor) + 1;
}