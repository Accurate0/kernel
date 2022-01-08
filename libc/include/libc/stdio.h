#pragma once
#include <stdarg.h>
#include <stddef.h>

int sprintf(char *str, const char *format, ...);
int vsprintf(char *str, const char *format, va_list args);
