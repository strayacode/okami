#include "kernel/string.h"

size_t string_length(const char *msg)
{
    size_t length = 0;
    while (*msg != '\0') {
        length++;
        msg++;
    }

    return length;
}