#ifndef PORT_H
#define PORT_H

#include <stdint.h>

void outb(uint16_t port, uint8_t data);
void cli(void);
void sti(void);

#endif