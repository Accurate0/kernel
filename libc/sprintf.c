#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include <libc/string.h>

int vsnprintf(char *str, size_t size, const char *format, va_list args) {
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

                case 'c':
                    const int c_arg = va_arg(args, int);
                    str[current++] = c_arg;
                    format++;
                    break;

                case 'd': {
                    static const char integer_map[] = {"0123456789"};
                    int int_val = va_arg(args, int);
                    bool neg = int_val < 0;

                    if (current >= size)
                        goto end_string;

                    if (neg) {
                        str[current++] = '-';
                        int_val = -int_val;
                    }

                    // this is a slightly deranged thing to do
                    if (int_val == 0) {
                        str[current++] = '0';
                    } else {
                        // int max '2147483647'
                        char buf[11] = {0};
                        for (int i = 0; int_val > 0; int_val /= 10, i++) {
                            if (current >= size)
                                goto end_string;

                            buf[i] = integer_map[int_val % 10];
                        }

                        for (int i = strlen(buf) - 1; i >= 0; i--) {
                            if (current >= size)
                                goto end_string;

                            str[current++] = buf[i];
                        }
                    }

                    format++;
                } break;
            }
        }

        if (*format == '\\') {
            format++;
            switch (*format) {
                case 'n': {
                    if (current < size)
                        goto end_string;

                    str[current] = '\n';
                } break;
            }
        }

        if (current < size) {
            str[current] = *format;
            format++;
            current++;
        } else {
            goto end_string;
        }
    }

end_string:
    str[current] = '\0';

    return current;
}

int snprintf(char *str, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsnprintf(str, size, format, args);
    va_end(args);

    return len;
}
