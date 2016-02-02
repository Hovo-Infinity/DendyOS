global loader                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes


section .bss
align 4                                     ; align at 4 bytes
kernel_stack:                               ; label points to beginning of memory
    resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel

section .text:                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

loader:                         ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the
                                            ; stack (end of memory area)
    ; The assembly code
    extern clear_screen
    call clear_screen
    extern kmain           ; the function sum_of_three is defined elsewhere
    push dword 3            ; arg3
    push dword 2            ; arg2
    push dword 1            ; arg1
    call kmain       ; call the function, the result will be in eax
.loop:
    jmp .loop                   ; loop forever

global outb             ; make the label outb visible outside this file
    ; outb - send a byte to an I/O port
    ; stack: [esp + 8] the data byte
    ;        [esp + 4] the I/O port
    ;        [esp    ] return address
outb:
    mov al, [esp + 8]    ; move the data to be sent into the al register
    mov dx, [esp + 4]    ; move the address of the I/O port into the dx register
    out dx, al           ; send the data to the I/O port
    ret                  ; return to the calling function