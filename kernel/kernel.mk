CFILES += $(wildcard kernel/*.c)
CFILES += $(wildcard kernel/arch/$(ARCH)/*.c)
SFILES += $(wildcard kernel/arch/$(ARCH)/*.s)