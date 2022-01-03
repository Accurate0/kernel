#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/instructions.h>
#include <kernel/multiboot.h>
#include <kernel/printk.h>
#include <kernel/serial.h>
#include <kernel/tty.h>

#include <libc/stdio.h>

#include <ext/printf.h>

#define VERSION "0.1"

#define KEEP_ALIVE() \
    for (;;)         \
        ;

void init(multiboot_info_t *info) {
    tty_init();
    serial_init();
    gdt_init();
    idt_init();

    printk(PRINTK_SERIAL | PRINTK_TTY, "mem: %d -> %d\n", info->mem_lower, info->mem_upper);

    // mask all but keyboard interrupts
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    sti();

    KEEP_ALIVE();
}
