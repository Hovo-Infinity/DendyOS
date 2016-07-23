#################################
#####   Dendy OS makefile   #####
#####   David Hovhannisyan  #####
#################################


#################################
#####   Source dependencies #####
#################################
KERNEL_DIR = kernel
KERNEL_ASM_DIR = asm
KERNEL_C_DIR = c
KERNEL_ASM := $(addprefix $(KERNEL_DIR)/$(KERNEL_ASM_DIR)/, loader.o)
KERNEL_C := $(addprefix $(KERNEL_DIR)/$(KERNEL_C_DIR)/, kmain.o)
KERNEL_EXEC := $(addprefix $(KERNEL_DIR)/, kernel.elf)

GDT_DIR = gdt
GDT := $(addprefix $(GDT_DIR)/, gdt.o)

BOCHS_DIR = bochs
BOCHS_SRC := $(addprefix $(BOCHS_DIR)/, bochsrc.txt)

#################################
#####   C language compiler #####
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
###################################


#####   objects linker   #####
LINKER_DIR = linker
LINKER := $(addprefix $(LINKER_DIR)/, link.ld)


LDFLAGS = -T $(LINKER) -melf_i386
##############################

#####   x86 assembly compiler   #####
AS = nasm
ASFLAGS = -f elf
#####################################

all: $(KERNEL_EXEC)

$(KERNEL_EXEC): $(KERNEL_ASM) $(KERNEL_C) $(GDT)
	ld $(LDFLAGS) $(KERNEL_ASM) $(KERNEL_C) $(GDT) -o $(KERNEL_EXEC)

dendy_os.iso: $(KERNEL_EXEC)
	cp $(KERNEL_EXEC) iso/boot/kernel.elf
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A dendy_os                     \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o dendy_os.iso                 \
				iso

run: dendy_os.iso
	bochs -f $(BOCHS_SRC) -q

$%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf $(KERNEL_ASM) $(KERNEL_C) $(KERNEL_EXEC)