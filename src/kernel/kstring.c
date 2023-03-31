#include "kernel/kstring.h"

size_t kstrlen(const char *msg)
{
    size_t length = 0;
    while (*msg != '\0') {
        length++;
        msg++;
    }

    return length;
}