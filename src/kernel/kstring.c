#include <stdint.h>
#include "kernel/kstring.h"

size_t kstrlen(const char *msg) {
    size_t length = 0;
    while (*msg != '\0') {
        length++;
        msg++;
    }

    return length;
}

void *memset(void *b, int c, size_t len) {
    uint8_t *p = (uint8_t *)b;
    for (int i = 0; i < len; i++) {
        p[i] = (uint8_t)c;
    }
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;
    for (int i = 0; i < n; i++) {
        if (p1[i] < p2[i]) {
            return -1;
        } else if (p1[i] > p2[i]) {
            return 1;
        }
    }

    return 0;
}