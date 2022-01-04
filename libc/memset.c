#include <stddef.h>
#include <stdint.h>

void *memset(void *ptr, int value, size_t n) {
    uint8_t *ptr_byte = (uint8_t *)ptr;

    for (size_t i = 0; i < n; ptr_byte[i] = (uint8_t)value, i++)
        ;

    return ptr;
}
