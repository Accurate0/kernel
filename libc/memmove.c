#include <stddef.h>
#include <stdint.h>

#include <libc/string.h>

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t buf[n];
    memcpy(buf, src, n);
    memcpy(dest, buf, n);

    return dest;
}
