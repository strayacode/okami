TOOLCHAIN ?= gcc
ARCH ?= riscv64
QEMU := qemu-system-$(ARCH)
BUILD := build
BINARY := kernel.elf

CFLAGS := -Wall -Wextra -c
LDFLAGS := -T meta/scripts/$(ARCH).ld
QEMUFLAGS := -kernel $(BUILD)/$(BINARY)

include meta/toolchains/$(TOOLCHAIN).mk
include meta/scripts/qemu-$(ARCH).mk
include src/kernel/kernel.mk

OFILES := $(patsubst %.c,$(BUILD)/%.c.o,$(CFILES))
OFILES += $(patsubst %.s,$(BUILD)/%.s.o,$(SFILES))
DIRS := $(dir $(CFILES) $(SFILES))

.SILENT: create_build_dirs

all: create_build_dirs kernel 

kernel: $(OFILES)
	$(LD) -o $(BUILD)/$(BINARY) $(LDFLAGS) $^ 

create_build_dirs:
	mkdir -p $(BUILD); \
	for dir in $(DIRS); \
	do \
	mkdir -p $(BUILD)/$$dir; \
	done

$(BUILD)/%.s.o: %.s
	$(AS) -c $< -o $@ 

$(BUILD)/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@

qemu:
	$(QEMU) $(QEMUFLAGS)

clean:
	rm -r $(BUILD)