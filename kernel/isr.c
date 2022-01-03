#include <kernel/printk.h>

__attribute__((noreturn)) void isr_halt(void);
void isr_halt() {
    printk("INTERRUPT HANDLER\n");
    __asm__ volatile("cli; hlt");
}
