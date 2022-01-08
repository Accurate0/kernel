#include <kernel/instructions.h>
#include <kernel/printk.h>

__attribute__((noreturn)) void panic(const char *s) {
    // print to all outputs
    printk(0xFF, "PANIC: %s\n", s);
    cli();
    hlt();
}
