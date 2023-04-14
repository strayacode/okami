CFLAGS := -m32 -target i386-none-elf -ffreestanding -Wall -Wextra -nostdlib -c -I..

CFILES := $(wildcard *.c)
CFILES += $(wildcard $(ARCH)/*.c)
SFILES := $(wildcard $(ARCH)/*.s)
OFILES := $(patsubst %.c,$(BUILDDIR)/src/kernel/%.c.o,$(CFILES))
OFILES += $(patsubst %.s,$(BUILDDIR)/src/kernel/%.s.o,$(SFILES))

DIRS := src/kernel src/kernel/x86
LDFLAGS := -Ttext 0x9000 -T $(ARCH)/linker.ld --oformat=binary

all: $(OFILES)
	$(LD) $(LDFLAGS) $^ -o $(BUILDDIR)/kernel.bin

create_build_dirs:
	for dir in $(DIRS); \
	do \
	mkdir -p $(BUILDDIR)/$$dir; \
	done

$(BUILDDIR)/%.s.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(BUILDDIR)/src/kernel/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@