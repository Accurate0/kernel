#include <tty.h>
#include <multiboot.h>
#include <interrupt.h>

#include <libc/stdio.h>

void init(multiboot_info_t *info)
{
    char buffer[512] = { 0 };
    /* Initialize terminal interface */
    tty_init();
    snprintf(buffer, 512, "mem: %d -> %d\n", info->mem_lower, info->mem_upper);
    tty_print(buffer);

    for(;;) {}
}
