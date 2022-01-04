#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H

#include <stdint.h>

void pic_irq_ack(uint8_t irq);
void pic_init();

#endif
