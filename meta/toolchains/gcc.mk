CC = $(ARCH)-unknown-elf-gcc
AS = $(ARCH)-unknown-elf-as
LD = $(ARCH)-unknown-elf-ld
CFLAGS += -mcmodel=medany -ffreestanding -nostdlib -Isrc/
LDFLAGS += -nostdlib