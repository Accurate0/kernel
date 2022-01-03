#include <kernel/tty.h>
#include <libc/stdio.h>
#include <libc/string.h>

#include <stdarg.h>

static inline int printk(const char *s, ...) {
    char buf[256] = {0};

    va_list args;
    va_start(args, s);

    int len = vsnprintf(buf, 256, s, args);

    va_end(args);

    tty_set_color(VGA_COLOR_RED, VGA_COLOR_BLACK);
    tty_print(buf);
    tty_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    return len;
}
