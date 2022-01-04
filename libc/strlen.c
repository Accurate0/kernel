#include <stddef.h>

size_t strlen(const char *str) {
    const char *a = str;
    for (; *str; str++)
        ;
    return str - a;
}
size_t strnlen(const char *str, size_t n) {
    size_t current = 0;
    const char *p = str;
    while (*(++p)) {
        if (current >= n) {
            return n;
        }

        current++;
    }

    return p - str;
}
