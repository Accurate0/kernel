#include <kernel/device/pic.h>
#include <kernel/instructions.h>
#include <kernel/isr.h>
#include <kernel/printk.h>

#include <stddef.h>

// For both exceptions and irq interrupt
isr_t interrupt_handlers[256];
char *exception_messages[32] = {"Division By Zero",
                                "Debug",
                                "Non Maskable Interrupt",
                                "Breakpoint",
                                "Into Detected Overflow",
                                "Out of Bounds",
                                "Invalid Opcode",
                                "No Coprocessor",
                                "Double Fault",
                                "Coprocessor Segment Overrun",
                                "Bad TSS",
                                "Segment Not Present",
                                "Stack Fault",
                                "General Protection Fault",
                                "Page Fault",
                                "Unknown Interrupt",
                                "Coprocessor Fault",
                                "Alignment Check",
                                "Machine Check",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved",
                                "Reserved"};

void final_exception_handler(register_t reg) {
    if (reg.int_no < 32) {
        printk(PRINTK_SERIAL | PRINTK_TTY, "EXCEPTION: %s (err code is %d)\n",
               exception_messages[reg.int_no], reg.err_code);
        for (;;)
            ;
    }
    if (interrupt_handlers[reg.int_no] != NULL) {
        isr_t handler = interrupt_handlers[reg.int_no];
        handler(&reg);
    }
}

void register_interrupt_handler(int num, isr_t handler) {
    if (num < 256)
        interrupt_handlers[num] = handler;
}

void final_irq_handler(register_t *reg) {
    if (interrupt_handlers[reg->int_no] != NULL) {
        isr_t handler = interrupt_handlers[reg->int_no];
        handler(reg);
    }
    pic_irq_ack(reg->int_no);
}
