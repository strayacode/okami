#include <stddef.h>
#include <stdint.h>

void kmain(void)
{
    const uint16_t color = 0x0f00;
    const char *str = "Hello, World!";
    uint16_t *vga = (uint16_t *)0xb8000;
    
    for (int i = 0; i < 16; i++)
    {
        vga[i] = color | str[i];
    }
}