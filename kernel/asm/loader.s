; kernel start
global loader                   ; the entry symbol for ELF

; constants
MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes

; macros
%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    cli
    push    dword 0                     ; push 0 as error code
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    cli
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro


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
    extern clear_screen
    call clear_screen
    extern kmain            ; the function sum_of_three is defined elsewhere
    call kmain              ; call the function, the result will be in eax
    cli
.loop:
    hlt
    jmp .loop                   ; loop forever
;loader endp

global outb             ; make the label outb visible outside this file
    ; outb - send a byte to an I/O port
    ; stack: [esp + 8] the data byte
    ;        [esp + 4] the I/O port
    ;        [esp    ] return address
outb:
    mov al, [esp + 8]    ; move the data to be sent into the al register
    mov dx, [esp + 4]    ; move the address of the I/O port into the dx register
    out dx, al           ; send the data to the I/O port
    ret 8                ; return to the calling function
;outb endp

; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'
global gdt_flush     ; Allows the C code to link to this
extern gp            ; Says that 'gp' is in another file
gdt_flush:
    lgdt [gp]        ; Load the GDT with our 'gp' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush_cs   ; 0x08 is the offset to our code segment: Far jump!
flush_cs:
    ret               ; Returns back to the C code!

; Loads the IDT defined in 'idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

common_interrupt_handler:               ; the common parts of the generic interrupt handler
; save the registers
push eax
push ecx
push edx
push ebx
push esp
push ebp
push esi
push edi
; call the C function
extern interrupt_handler
call    interrupt_handler
; restore the registers
pop edi
pop esi
pop ebp
pop esp
pop ebx
pop edx
pop ecx
pop eax
; restore the esp
add     esp, 8
sti
; return to the code that got interrupted
iret

global handler_0
handler_0:
no_error_code_interrupt_handler 0       ; create handler for interrupt 0

global handler_3
handler_3:
no_error_code_interrupt_handler 3       ; create handler for interrupt 3
