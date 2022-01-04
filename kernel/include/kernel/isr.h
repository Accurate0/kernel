#ifndef KERNEL_ISR_H
#define KERNEL_ISR_H

#include <stdint.h>

typedef struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} register_t;

// Interrupt Service Routine function prototype
typedef void (*isr_t)(register_t *);

// Defined in exception.c
void final_exception_handler(register_t reg);

// Defined in interrupt.c
extern isr_t interrupt_handlers[256];
void register_interrupt_handler(int num, isr_t handler);
void final_irq_handler(register_t *reg);

// Defined in exception_helper.asm
extern void exception0();
extern void exception1();
extern void exception2();
extern void exception3();
extern void exception4();
extern void exception5();
extern void exception6();
extern void exception7();
extern void exception8();
extern void exception9();
extern void exception10();
extern void exception11();
extern void exception12();
extern void exception13();
extern void exception14();
extern void exception15();
extern void exception16();
extern void exception17();
extern void exception18();
extern void exception19();
extern void exception20();
extern void exception21();
extern void exception22();
extern void exception23();
extern void exception24();
extern void exception25();
extern void exception26();
extern void exception27();
extern void exception28();
extern void exception29();
extern void exception30();
extern void exception31();
extern void exception128();

// Defined in interrupt_helper.asm
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// Some IRQ constants
#define IRQ_BASE            0x20
#define IRQ0_Timer          (IRQ_BASE + 0x00)
#define IRQ1_Keyboard       (IRQ_BASE + 0x01)
#define IRQ2_CASCADE        (IRQ_BASE + 0x02)
#define IRQ3_SERIAL_PORT2   (IRQ_BASE + 0x03)
#define IRQ4_SERIAL_PORT1   (IRQ_BASE + 0x04)
#define IRQ5_RESERVED       (IRQ_BASE + 0x05)
#define IRQ6_DISKETTE_DRIVE (IRQ_BASE + 0x06)
#define IRQ7_PARALLEL_PORT  (IRQ_BASE + 0x07)

#define IRQ_2_BASE (IRQ_BASE + 8)

#define IRQ8_CMOS_CLOCK (IRQ_2_BASE + 0x00)
#define IRQ9_CGA        (IRQ_2_BASE + 0x01)
#define IRQ10_RESERVED  (IRQ_2_BASE + 0x02)
#define IRQ11_RESERVED  (IRQ_2_BASE + 0x03)
#define IRQ12_AUXILIARY (IRQ_2_BASE + 0x04)
#define IRQ13_FPU       (IRQ_2_BASE + 0x05)
#define IRQ14_HARD_DISK (IRQ_2_BASE + 0x06)
#define IRQ15_RESERVED  (IRQ_2_BASE + 0x07)

#endif
