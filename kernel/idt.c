#include <stdbool.h>

#include <kernel/idt.h>
#include <kernel/printk.h>
#include <kernel/tty.h>

#include <ext/printf.h>

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;
static bool vectors[IDT_MAX_DESCRIPTORS];

void idt_set_descriptor(uint8_t vector, uintptr_t isr, uint8_t flags) {
    idt_entry_t *descriptor = &idt[vector];

    descriptor->base_low = isr & 0xFFFF;
    descriptor->base_high = (isr >> 16) & 0xFFFF;
    descriptor->sel = 0x08;
    descriptor->zero = 0;
    descriptor->flags = flags | 0x60;
}

extern void *isr_stub_table[];

void idt_init() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, (uintptr_t)isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile("lidt %0" : : "m"(idtr)); // load the new IDT
}
