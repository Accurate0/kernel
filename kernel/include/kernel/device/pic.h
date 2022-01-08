#pragma once

#include <stdint.h>

void pic_irq_ack(uint8_t irq);
void pic_init();
