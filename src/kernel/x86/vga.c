#include <stdint.h>
#include "kernel/string.h"
#include "kernel/x86/vga.h"

#define VGA_BUFFER 0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef enum {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHTGRAY = 7,
    VGA_DARKGRAY = 8,
    VGA_LIGHTBLUE = 9,
    VGA_LIGHTGREEN = 10,
    VGA_LIGHTCYAN = 11,
    VGA_LIGHTRED = 12,
    VGA_PINK = 13,
    VGA_YELLOW = 14,
    VGA_WHITE = 15,
} colour_t;

static int row;
static int column;
static int colour_code;
static uint16_t *buffer;

static uint8_t vga_construct_colour_code(uint8_t fg, uint8_t bg)
{
    return fg | (bg << 4);
}

static uint16_t vga_construct_entry(char ch, uint8_t colour_code)
{
    return ch | (colour_code << 8);
}

static void vga_set(char ch, uint8_t colour_code)
{
    if (ch == '\n') {
        column = 0;
        row++;
        return;
    }

    buffer[(row * VGA_WIDTH) + column] = ch | (colour_code << 8);
    column++;

    if (column >= VGA_WIDTH) {
        column = 0;
        row++;
    }
}

// initialise vga text mode
// this allows us to display characters into a 80x25 grid
void vga_init(void)
{
    row = 0;
    column = 0;
    colour_code = vga_construct_colour_code(VGA_WHITE, VGA_BLACK);
    buffer = (uint16_t *)VGA_BUFFER;

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            buffer[(y * VGA_WIDTH) + x] = vga_construct_entry(' ', colour_code);
        }
    }
}

void vga_print(const char *msg)
{
    size_t length = string_length(msg);
    for (size_t i = 0; i < length; i++) {
        vga_set(msg[i], colour_code);
    }
}