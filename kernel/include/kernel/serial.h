#ifndef KERNEL_SERIAL_H
#define KERNEL_SERIAL_H
#include <stddef.h>

void serial_init();
void serial_putchar(char a);
void serial_print(const char *s);

#define SERIAL_ANSI_RED    "\e[31m"
#define SERIAL_ANSI_GREEN  "\e[32m"
#define SERIAL_ANSI_YELLOW "\e[33m"
#define SERIAL_ANSI_BLUE   "\e[34m"
#define SERIAL_ANSI_RESET  "\e[0m"
#endif
