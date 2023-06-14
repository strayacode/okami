CFILES += $(wildcard src/kernel/*.c)
CFILES += $(wildcard src/kernel/$(ARCH)/*.c)
SFILES += $(wildcard src/kernel/$(ARCH)/*.s)