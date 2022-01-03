#include <kernel/instructions.h>
#include <kernel/printk.h>

__attribute__((noreturn)) void isr_halt() {
    printk(PRINTK_SERIAL | PRINTK_TTY, "INTERRUPT HANDLER\n");
    cli();
    hlt();
}
