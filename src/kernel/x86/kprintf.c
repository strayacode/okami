#include <stdarg.h>
#include <stddef.h>
#include "kernel/x86/vga.h"
#include "kernel/kstring.h"
#include "kernel/kstdio.h"

static void print_number(int val, int base) {
    static char *digits = "0123456789ABCDEF";
    int buffer[100];
    int i = 0;

    if (val == 0) {
        kputchar('0');
        return;
    }

    if (base == 10 && val < 0) {
        kputchar('-');
        val = -val;
    }

    while (val) {
        int digit = val % base;
        val /= base;
        buffer[i++] = digit;
    }

    i--;

    while (i >= 0) {
        kputchar(digits[buffer[i]]);
        i--;
    }
}

static void print_string(const char *str) {
    size_t length = kstrlen(str);

    for (size_t i = 0; i < length; i++) {
        kputchar(str[i]);
    }
}

int kputchar(int c) {
    vga_putchar(c);

    // TODO: figure out what the return value means
    return 0;
}

int kprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    size_t length = kstrlen(format);
    size_t i = 0;
    char c;

    while (i < length) {
        c = format[i];

        if (c == '%') {
            // TODO: handle i going out of bounds
            i++;
            c = format[i];

            switch (c) {
            case 'c':
                kputchar(c);
                i++;
                break;
            case 'd':
                print_number((int)va_arg(args, int), 10);
                i++;
                break;
            case 'x':
                print_number((int)va_arg(args, int), 16);
                i++;
                break;
            case 'o':
                print_number((int)va_arg(args, int), 16);
                i++;
                break;
            case 's':
                print_string((const char *)va_arg(args, const char *));
                i++;
                break;
            }
        } else {
            kputchar(c);
            i++;
        }
    }

    return 0;
}