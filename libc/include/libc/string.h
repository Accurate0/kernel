#pragma once
#include <stddef.h>

size_t strlen(const char *str);
size_t strnlen(const char *str, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *ptr, int value, size_t n);
void *memmove(void *dest, const void *src, size_t n);
