#ifndef PIC_H
#define PIC_H

#include <stdint.h>

void pic_init(void);
void pic_signal_eoi(uint8_t irq);

#endif