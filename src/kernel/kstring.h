#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t kstrlen(const char *msg);
void *memset(void *b, int c, size_t len);
int memcmp(const void *s1, const void *s2, size_t n);

#endif