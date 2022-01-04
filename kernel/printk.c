#include <kernel/printk.h>
#include <kernel/serial.h>
#include <kernel/tty.h>

#include <libc/stdio.h>
#include <libc/string.h>

#include <stdarg.h>
#include <stdbool.h>

int printk(int output, const char *s, ...) {
    char buf[256] = {0};

    va_list args;
    va_start(args, s);

    int len = vsnprintf(buf, 256, s, args);

    va_end(args);

    // write to tty
    if (output & PRINTK_TTY) {
        tty_set_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
        tty_print("Kernel: ");
        tty_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
        tty_print(buf);
    }

    if (output & PRINTK_SERIAL) {
        // write to serial
        serial_print(SERIAL_ANSI_GREEN "Kernel: " SERIAL_ANSI_RESET);
        serial_print(buf);
    }

    return len;
}
