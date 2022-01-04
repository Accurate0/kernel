#include <kernel/instructions.h>
#include <kernel/pic.h>

#define PIC1         0x20
#define PIC2         0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA    (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA    (PIC2 + 1)
#define PIC_EOI      0x20

#define ICW1 0x11
#define ICW4 0x01

/*
 * PIC is very complex, for a better understanding, visist
 * http://www.brokenthorn.com/Resources/OSDevPic.html or some other materials that explain PIC,
 * otherwise the following code is impossible to uderstand....
 * */
void pic_init() {
    // ICW1
    outb(PIC1_COMMAND, ICW1);
    outb(PIC2_COMMAND, ICW1);

    // ICW2, irq 0 to 7 is mapped to 0x20 to 0x27, irq 8 to F is mapped to 28 to 2F
    outb(PIC1_DATA, 0x20);
    outb(PIC2_DATA, 0x28);

    // ICW3, connect master pic with slave pic
    outb(PIC1_DATA, 0x4);
    outb(PIC2_DATA, 0x2);

    // ICW4, set x86 mode
    outb(PIC1_DATA, 1);
    outb(PIC2_DATA, 1);

    // clear the mask register
    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 0);
}

/*
 * Tell PIC interrupt is handled
 * */
void pic_irq_ack(uint8_t irq) {
    if (irq >= 0x28)
        outb(PIC2, PIC_EOI);
    outb(PIC1, PIC_EOI);
}
