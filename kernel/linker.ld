/* declare entrypoint of binary */
ENTRY(_start)

SECTIONS
{
    /* start putting sections at 1mb (by convention) */
    . = 1M;

    /* put multiboot header */
    .text ALIGN(4K) :
    {
        *(.text)
    }

    /* read-only data */
    .rodata ALIGN(4K) :
    {
        *(.rodata)
    }

    /* read-write data */
    .data ALIGN(4K) :
    {
        *(.bss)
    }
}