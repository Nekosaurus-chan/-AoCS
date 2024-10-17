C = gcc
ASM = nasm

DIR = .
EXE = kernel

CSOURCES = kernel.c
CSOURCES += $(DIR)/vga/vga.c $(DIR)/gdt/gdt.c $(DIR)/lib/itoa.c 
COBJS = $(addsuffix .o, $(basename $(notdir $(CSOURCES))))

ASMSOURCES = boot.s
ASMSOURCES += $(DIR)/gdt/gdt.s $(DIR)/cpu_mode/cpu_mode.s
ASMOBJS = $(addsuffix _s.o, $(basename $(notdir $(ASMSOURCES))))

CFLAGS = -m32 -fno-stack-protector -nostdlib -Wall -Wformat
CFLAGS += -g -I$(DIR)/vga -I$(DIR)/gdt -I$(DIR)/lib

ASMFLAGS = -g -f elf32
ASMFLAGS += -I$(DIR)/gdt

clean:
	rm -f *.o
	rm -f *.iso

cbuild: $(COBJS)

%.o: $(DIR)/%.c
	$(C) $(CFLAGS) -c $< -o $@

%.o: $(DIR)/vga/%.c
	$(C) $(CFLAGS) -c $< -o $@

%.o: $(DIR)/gdt/%.c
	$(C) $(CFLAGS) -c $< -o $@

%.o: $(DIR)/lib/%.c
	$(C) $(CFLAGS) -c $< -o $@

asmbuild: $(ASMOBJS)

%_s.o: $(DIR)/%.s
	$(ASM) $(ASMFLAGS) $< -o $@

%_s.o: $(DIR)/gdt/%.s
	$(ASM) $(ASMFLAGS) $< -o $@

%_s.o: $(DIR)/cpu_mode/%.s
	$(ASM) $(ASMFLAGS) $< -o $@

link:
	ld -m elf_i386 -T linker.ld -o $(EXE) $(COBJS) $(ASMOBJS)

image:
	mv $(EXE) os/boot/$(EXE)
	grub-mkrescue -o os.iso os/

all: clean cbuild asmbuild link image
	@echo Build complete for $(EXE)
