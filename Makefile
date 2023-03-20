BUILDDIR := build
SOURCEDIR := kernel
CC := clang
ASM := nasm
LD := ld.lld
QEMU := qemu-system-i386

CFLAGS := -m32 -target i386-none-elf -ffreestanding -Wall -Wextra -nostdlib -c
ASMFLAGS := -f elf32
LDFLAGS := -T kernel/linker.ld --oformat=elf
QEMUFLAGS := -kernel

ARCH := x86

include kernel/kernel.mk

OFILES := $(patsubst %.c,$(BUILDDIR)/%.o,$(CFILES))
OFILES += $(patsubst %.s,$(BUILDDIR)/%.o,$(SFILES))
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

$(BUILDDIR)/%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

qemu:
	$(QEMU) $(QEMUFLAGS) $(BUILDDIR)/kernel.elf

clean:
	rm -r $(BUILDDIR)