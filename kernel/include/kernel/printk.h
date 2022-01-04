#ifndef KERNEL_PRINTK_H
#define KERNEL_PRINTK_H
enum
{
    PRINTK_SERIAL = 1 << 0,
    PRINTK_TTY = 1 << 1,
};
int printk(int output, const char *s, ...);
#endif
