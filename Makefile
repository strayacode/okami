OUTDIR := build
SOURCES := kernel
CC := clang
ASM := nasm
LD := ld.lld
QEMU := qemu-system-i386

CFLAGS := -m32 -target i386-none-elf -ffreestanding -Wall -Wextra -nostdlib -c
ASMFLAGS := -f elf
LDFLAGS := -Ttext 0x7c00 -T kernel/linker.ld --oformat=binary
QEMUFLAGS := -fda

CFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
ASMFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))

HFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.h))
OFILES := $(patsubst %.c,$(OUTDIR)/%.o,$(CFILES))
OFILES += $(patsubst %.s,$(OUTDIR)/%.o,$(ASMFILES))

.SILENT: create_build_dirs

all: create_build_dirs kernel 

kernel: $(OFILES)
	$(LD) $(LDFLAGS) $^ -o kernel.bin

create_build_dirs:
	mkdir -p $(OUTDIR); \
	for dir in $(SOURCES); \
	do \
	mkdir -p $(OUTDIR)/$$dir; \
	done

$(OUTDIR)/%.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

qemu:
	$(QEMU) $(QEMUFLAGS) kernel.bin