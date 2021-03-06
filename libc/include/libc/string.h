#ifndef LIBC_STRING_H
#define LIBC_STRING_H
#include <stddef.h>

size_t strlen(const char *str);
void *memcpy(void *dest, const void *src, size_t n);

#endif