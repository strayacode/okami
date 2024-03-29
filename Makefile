BUILDDIR := build
CC := clang
ASM := nasm
LD := ld.lld
QEMU := qemu-system-i386

CFLAGS := -m32 -target i386-none-elf -ffreestanding -Wall -Wextra -nostdlib -c -Isrc/
ASMFLAGS := -f elf
LDFLAGS := -T src/kernel/linker.ld --oformat=elf
QEMUFLAGS := -vga std -kernel

ARCH := x86

include src/kernel/Makefile

OFILES := $(patsubst %.c,$(BUILDDIR)/%.c.o,$(CFILES))
OFILES += $(patsubst %.s,$(BUILDDIR)/%.s.o,$(SFILES))
DIRS := $(dir $(CFILES) $(SFILES))

.SILENT: create_build_dirs

all: create_build_dirs kernel 

kernel: $(OFILES)
	$(LD) $(LDFLAGS) $^ -o $(BUILDDIR)/kernel.elf

create_build_dirs:
	mkdir -p $(BUILDDIR); \
	for dir in $(DIRS); \
	do \
	mkdir -p $(BUILDDIR)/$$dir; \
	done

$(BUILDDIR)/%.s.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(BUILDDIR)/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@

qemu:
	$(QEMU) $(QEMUFLAGS) $(BUILDDIR)/kernel.elf

clean:
	rm -r $(BUILDDIR)