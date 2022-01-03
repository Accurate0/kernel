#ifndef KERNEL_IDT_H
#define kERNEL_IDT_H
#include <stdint.h>

typedef struct {
    uint16_t base_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed)) idtr_t;

#define IDT_MAX_DESCRIPTORS 256

void idt_init();

#endif
