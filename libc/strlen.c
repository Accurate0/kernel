#include <stddef.h>

size_t strlen(const char *str)
{
    const char *p = str;
    while(*(++p));

    return(p - str);
}
