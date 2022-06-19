#include <kernel/device/keyboard.h>
#include <kernel/device/pic.h>
#include <kernel/device/serial.h>
#include <kernel/device/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/instructions.h>
#include <kernel/memory/pmm.h>
#include <kernel/multiboot.h>
#include <kernel/panic.h>
#include <kernel/printk.h>

extern void kmain_rs();

void kmain(multiboot_info_t *mb_info) {
    tty_init();
    serial_init();
    gdt_init();
    idt_init();

    pic_init();
    keyboard_init();

    pmm_init(mb_info->mmap_addr, mb_info->mmap_length);

    // mask all but keyboard interrupts
    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    sti();

    kmain_rs();
}
