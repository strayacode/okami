BUILDDIR := $(shell pwd)/build
CC := clang
ASM := nasm
LD := ld.lld
QEMU := qemu-system-i386
ARCH := x86
QEMUFLAGS := -s -drive file=$(BUILDDIR)/disk.img,index=0,media=disk,format=raw,if=ide

.SILENT: create_build_dirs

all: create_build_dirs loader kernel
	$(info creating disk image...)
	dd if=/dev/zero of=$(BUILDDIR)/disk.img bs=10M count=1
	dd if=$(BUILDDIR)/stage1.bin of=$(BUILDDIR)/disk.img bs=1 seek=0 count=$(shell stat -f%z $(BUILDDIR)/stage1.bin) conv=notrunc
	dd if=$(BUILDDIR)/stage2.bin of=$(BUILDDIR)/disk.img bs=1 seek=512 count=$(shell stat -f%z $(BUILDDIR)/stage2.bin) conv=notrunc
	dd if=$(BUILDDIR)/kernel.bin of=$(BUILDDIR)/disk.img bs=1 seek=1024 count=$(shell stat -f%z $(BUILDDIR)/kernel.bin) conv=notrunc
	$(info stage1 contains $(shell echo $$((($(shell stat -f%z $(BUILDDIR)/stage1.bin) + 511) / 512))) sector(s))
	$(info stage2 contains $(shell echo $$((($(shell stat -f%z $(BUILDDIR)/stage2.bin) + 511) / 512))) sector(s))
	$(info kernel contains $(shell echo $$((($(shell stat -f%z $(BUILDDIR)/kernel.bin) + 511) / 512))) sector(s))

kernel:
	make -C src/kernel BUILDDIR=$(BUILDDIR) CC=$(CC) ASM=$(ASM) LD=$(LD) ARCH=$(ARCH) all

loader:
	make -C src/loader/$(ARCH) BUILDDIR=$(BUILDDIR) ASM=$(ASM) LD=$(LD) all

create_build_dirs:
	make -C src/loader/$(ARCH) BUILDDIR=$(BUILDDIR) create_build_dirs
	make -C src/kernel BUILDDIR=$(BUILDDIR) create_build_dirs

qemu:
	$(QEMU) $(QEMUFLAGS)

clean:
	rm -r $(BUILDDIR)