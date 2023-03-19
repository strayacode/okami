BUILDDIR := build
SOURCES := kernel
CC := clang
ASM := nasm
LD := ld.lld
QEMU := qemu-system-i386

CFLAGS := -m32 -target i386-none-elf -ffreestanding -Wall -Wextra -nostdlib -c
ASMFLAGS := -f elf32
LDFLAGS := -T kernel/linker.ld --oformat=elf
QEMUFLAGS := -machine type=pc-i440fx-3.1 -kernel

CFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
ASMFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))

HFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.h))
OFILES := $(patsubst %.c,$(BUILDDIR)/%.o,$(CFILES))
OFILES += $(patsubst %.s,$(BUILDDIR)/%.o,$(ASMFILES))

.SILENT: create_build_dirs

all: create_build_dirs kernel 

kernel: $(OFILES)
	$(LD) $(LDFLAGS) $^ -o $(BUILDDIR)/kernel.elf

create_build_dirs:
	mkdir -p $(BUILDDIR); \
	for dir in $(SOURCES); \
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