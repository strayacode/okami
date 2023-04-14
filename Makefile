BUILDDIR := $(shell pwd)/build
CC := clang
ASM := nasm
LD := ld.lld
QEMU := qemu-system-i386
ARCH := x86

CFLAGS := -m32 -target i386-none-elf -ffreestanding -Wall -Wextra -nostdlib -c -Isrc/
QEMUFLAGS := -drive file=$(BUILDDIR)/disk.img,index=0,media=disk,format=raw,if=ide

STAGE1_SIZE := $(shell stat -f%z $(BUILDDIR)/stage1.bin)
STAGE2_SIZE := $(shell stat -f%z $(BUILDDIR)/stage2.bin)

.SILENT: create_build_dirs

all: create_build_dirs loader
	$(info creating disk image...)
	dd if=/dev/zero of=$(BUILDDIR)/disk.img bs=64M count=1
	dd if=$(BUILDDIR)/stage1.bin of=$(BUILDDIR)/disk.img bs=1 seek=0 count=$(STAGE1_SIZE) conv=notrunc
	dd if=$(BUILDDIR)/stage2.bin of=$(BUILDDIR)/disk.img bs=1 seek=512 count=$(STAGE2_SIZE) conv=notrunc

kernel:
	# TODO: add the proper code once we can load stage2
	# make -C src/kernel all

loader:
	make -C src/loader/$(ARCH) BUILDDIR=$(BUILDDIR) ASM=$(ASM) LD=$(LD) all

create_build_dirs:
	make -C src/loader/$(ARCH) BUILDDIR=$(BUILDDIR) create_build_dirs

qemu:
	$(QEMU) $(QEMUFLAGS)

clean:
	rm -r $(BUILDDIR)