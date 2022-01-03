#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/interrupt.h>
#include <kernel/multiboot.h>
#include <kernel/printk.h>
#include <kernel/tty.h>

#include <libc/stdio.h>

#include <ext/printf.h>

#define VERSION "0.1"

#define KEEP_ALIVE() \
    for (;;)         \
        ;

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void init(multiboot_info_t *info) {
    char buffer[512] = {0};
    /* Initialize terminal interface */
    tty_init();

    printk("mem: %d -> %d\n", info->mem_lower, info->mem_upper);

    gdt_install();
    idt_init();

    // mask all but keyboard interrupts
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    sti();

    KEEP_ALIVE();
}
