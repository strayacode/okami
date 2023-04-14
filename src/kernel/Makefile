CFILES := $(wildcard src/kernel/*.c)
CFILES += $(wildcard src/kernel/$(ARCH)/*.c)
SFILES := $(wildcard src/kernel/$(ARCH)/*.s)

OFILES := $(patsubst %.c,$(BUILDDIR)/%.c.o,$(CFILES))
OFILES += $(patsubst %.s,$(BUILDDIR)/%.s.o,$(SFILES))

all: $(OFILES)
	# $(LD) $(LDFLAGS) $^ -o $(BUILDDIR)/kernel.bin

$(BUILDDIR)/%.s.o: %.s
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(BUILDDIR)/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@