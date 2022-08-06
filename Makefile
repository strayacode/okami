OUTDIR := build
SOURCES := kernel
CC := clang
ASM := nasm
LD := ld.lld
QEMU := qemu-system-i386

CFLAGS := -target i386-none-elf -ffreestanding -Wall -Wextra -nostdlib -c
ASMFLAGS := -f elf
LDFLAGS := -T kernel/linker.ld --oformat=binary
QEMUFLAGS := -fda

CFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
ASMFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))

HFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.h))
OFILES := $(patsubst %.c,$(OUTDIR)/%.o,$(CFILES))
OFILES += $(patsubst %.s,$(OUTDIR)/%.o,$(ASMFILES))

$(info ofiles is $(OFILES))

.SILENT: dirs

$(OUTDIR)/kernel/boot.o: kernel/boot.s
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

dirs:
	for dir in $(SOURCES); \
	do \
	mkdir -p $(OUTDIR)/$$dir; \
	done

all: $(OFILES) | dirs
	$(info    VAR is $(OFILES))
	$(LD) $(LDFLAGS) $^ -o kernel.bin

qemu:
	$(QEMU) $(QEMUFLAGS) kernel.bin