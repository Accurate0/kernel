extern "C" {
#include <kernel/printk.h>
}

#define KEEP_ALIVE() \
    for (;;)         \
        ;

class Kernel {
  public:
    void test() {
        printk(printk_output::PRINTK_SERIAL | printk_output::PRINTK_TTY, "test c++ function\n");
    }
};

extern "C" {
void kmain() {
    Kernel k;

    printk(printk_output::PRINTK_SERIAL | printk_output::PRINTK_TTY, "c++\n");
    k.test();

    KEEP_ALIVE();
}
}
