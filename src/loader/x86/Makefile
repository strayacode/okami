STAGE1_LDFLAGS := -Ttext 0x7c00 -T stage1/linker.ld --oformat=binary
STAGE2_LDFLAGS := -Ttext 0x7e00 -T stage2/linker.ld --oformat=binary
ASMFLAGS := -f elf
DIRS := src/loader/x86/stage1 src/loader/x86/stage2
STAGE1_NUM_SECTORS := $(shell echo $$((($(STAGE1_SIZE) + 511) / 512)))
STAGE2_NUM_SECTORS := $(shell echo $$((($(STAGE2_SIZE) + 511) / 512)))

all: stage1.bin stage2.bin 
	$(info stage1 contains $(STAGE1_NUM_SECTORS) sector(s))
	$(info stage2 contains $(STAGE2_NUM_SECTORS) sector(s))

stage1.bin:
	$(info building stage1...)
	$(ASM) $(ASMFLAGS) stage1/stage1.s -o $(BUILDDIR)/src/loader/x86/stage1/stage1.s.o
	$(LD) $(STAGE1_LDFLAGS) $(BUILDDIR)/src/loader/x86/stage1/stage1.s.o -o $(BUILDDIR)/stage1.bin
	
stage2.bin:
	$(info building stage2...)
	$(ASM) $(ASMFLAGS) stage2/stage2.s -o $(BUILDDIR)/src/loader/x86/stage2/stage2.s.o
	$(LD) $(STAGE2_LDFLAGS) $(BUILDDIR)/src/loader/x86/stage2/stage2.s.o -o $(BUILDDIR)/stage2.bin

.SILENT: create_build_dirs

create_build_dirs:
	for dir in $(DIRS); \
	do \
	mkdir -p $(BUILDDIR)/$$dir; \
	done

$(BUILDDIR)/%.s.o: %.s
	$(info $< $@)
	$(ASM) $(ASMFLAGS) $< -o $@ 