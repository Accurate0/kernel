#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <libc/string.h>

int vsprintf(char *str, const char *format, va_list args) {
    size_t current = 0;

    for (;;) {
        if (*format == '\0')
            break;

        if (*format == '%') {
            format++;
            switch (*format) {
                case 's':
                    const char *str_arg = va_arg(args, char *);
                    int len = strlen(str_arg);
                    memcpy(str + current, str_arg, len);
                    current += len;
                    format++;
                    break;

                case 'x':
                    int int_val = va_arg(args, int);
                    char buf[12] = {0};
                    static const char hex_map[] = {"0123456789ABCDEF"};

                    int i = 0;
                    while (1) {
                        buf[i++] = hex_map[int_val % 16];
                        int_val /= 16;

                        if (int_val == 0)
                            break;
                    }

                    str[current++] = '0';
                    str[current++] = 'x';

                    for (int i = strlen(buf) - 1; i >= 0; i--) {
                        str[current++] = buf[i];
                    }

                    memcpy(str + current, buf, strlen(buf));
                    format++;
                    break;

                case 'c':
                    const int c_arg = va_arg(args, int);
                    str[current++] = c_arg;
                    format++;
                    break;

                case 'd': {
                    static const char integer_map[] = {"0123456789"};
                    int int_val = va_arg(args, int);
                    bool neg = int_val < 0;

                    if (neg) {
                        str[current++] = '-';
                        int_val = -int_val;
                    }
                    char buf[64] = {0};

                    int i = 0;
                    while (1) {
                        buf[i++] = integer_map[int_val % 10];
                        int_val /= 10;

                        if (int_val == 0)
                            break;
                    }

                    for (int i = strlen(buf) - 1; i >= 0; i--) {
                        str[current++] = buf[i];
                    }

                    memcpy(str + current, buf, strlen(buf));
                    format++;
                } break;
            }
        }

        if (*format == '\\') {
            format++;
            switch (*format) {
                case 'n': {
                    str[current] = '\n';
                } break;
            }
        }

        str[current] = *format;
        format++;
        current++;
    }

    str[current] = '\0';

    return current;
}

int sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsprintf(str, format, args);
    va_end(args);

    return len;
}
