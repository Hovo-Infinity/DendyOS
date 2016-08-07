#################################
#####   Dendy OS makefile   #####
#################################


#################################
#####   Source dependencies #####
KERNEL_DIR = kernel
KERNEL_ASM_DIR = asm
KERNEL_C_DIR = c
KERNEL_ASM := $(addprefix $(KERNEL_DIR)/$(KERNEL_ASM_DIR)/, loader.o)
KERNEL_C := $(addprefix $(KERNEL_DIR)/$(KERNEL_C_DIR)/, kmain.o)
KERNEL_EXEC := $(addprefix $(KERNEL_DIR)/, kernel.elf)

UTILITY_DIR = utility
UTILITY := $(addprefix $(UTILITY_DIR)/, utility.o)

CONSOLE_DIR = console
CONSOLE := $(addprefix $(CONSOLE_DIR)/, console.o)

GDT_DIR = gdt
GDT := $(addprefix $(GDT_DIR)/, gdt.o)

IDT_DIR = idt
IDT := $(addprefix $(IDT_DIR)/, idt.o)
HANDLERS := $(addprefix $(IDT_DIR)/, handlers.o)

KERNEL_ARGS :=                  $(UTILITY)      \
                                $(CONSOLE)      \
                                $(GDT)          \
                                $(HANDLERS)     \
                                $(IDT)          \
                                $(KERNEL_ASM)   \
                                $(KERNEL_C)     \

BOCHS_DIR = bochs
BOCHS_SRC := $(addprefix $(BOCHS_DIR)/, bochsrc.txt)
#################################

#################################
#####   C language compiler #####
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
###################################

#####################################
#####   x86 assembly compiler   #####
AS = nasm
ASFLAGS = -f elf
#####################################

##############################
#####   objects linker   #####
LINKER_DIR = linker
LINKER := $(addprefix $(LINKER_DIR)/, link.ld)
LDFLAGS = -T $(LINKER) -melf_i386
##############################

all: $(KERNEL_EXEC)

$(KERNEL_EXEC): $(KERNEL_ARGS)
	ld $(LDFLAGS) $(KERNEL_ARGS) -o $(KERNEL_EXEC)

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
	rm -rf $(KERNEL_ARGS) $(KERNEL_EXEC)
