#pragma once
#include <stdint.h>
enum
{
    PRINTK_SERIAL = 1 << 0,
    PRINTK_TTY = 1 << 1,
};
int _printk(const char *caller, uint8_t output, const char *s, ...);

#define printk(output, s, ...) _printk(__func__, output, s, ##__VA_ARGS__)
