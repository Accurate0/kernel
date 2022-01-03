#include <kernel/serial.h>
#include <kernel/tty.h>

void _putchar(char c) {
    tty_putchar(c);
    serial_putchar(c);
}
