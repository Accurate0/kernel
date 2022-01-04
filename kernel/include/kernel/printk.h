#ifndef KERNEL_PRINTK_H
#define KERNEL_PRINTK_H
enum
{
    PRINTK_SERIAL = 1,
    PRINTK_TTY = 2,
};
int printk(int output, const char *s, ...);
#endif
