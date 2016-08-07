; kernel start
global loader                   ; the entry symbol for ELF

; constants
MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096*3      ; size of stack in bytes

; macros
%macro no_error_code_interrupt_handler 1
global handler_%1
handler_%1:
    cli
    push    dword 0                     ; push 0 as error code
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
global handler_%1
handler_%1:
    cli
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro


section .bss
align 4                                 ; align at 4 bytes
    resb KERNEL_STACK_SIZE              ; reserve stack for the kernel
kernel_stack:                           ; label points to beginning of memory

section .multiboot              ; start of the multiboot (code) section
align 4                         ; the code must be 4 byte aligned
dd MAGIC_NUMBER                 ; write the magic number to the machine code,
dd FLAGS                        ; the flags,
dd CHECKSUM                     ; and the checksum



section .text:                  ; start of the text (code) section
; the loader label (defined as entry point in linker script)
loader:
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
;gdt_flush endp

; Loads the IDT defined in 'idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret
;idt_load endp

; the common parts of the generic interrupt handler
common_interrupt_handler:
pushad
extern interrupt_handler
call    interrupt_handler
popad
add     esp, 8
iret
;common_interrupt_handler endp

no_error_code_interrupt_handler 0       ; create handler for interrupt 0
no_error_code_interrupt_handler 1       ; create handler for interrupt 1
no_error_code_interrupt_handler 2       ; create handler for interrupt 2
no_error_code_interrupt_handler 3       ; create handler for interrupt 3
no_error_code_interrupt_handler 4       ; create handler for interrupt 4
no_error_code_interrupt_handler 5       ; create handler for interrupt 5
no_error_code_interrupt_handler 6       ; create handler for interrupt 6
no_error_code_interrupt_handler 7       ; create handler for interrupt 7
error_code_interrupt_handler    8       ; create handler for interrupt 8
no_error_code_interrupt_handler 9       ; create handler for interrupt 9
error_code_interrupt_handler    10      ; create handler for interrupt 10
error_code_interrupt_handler    11      ; create handler for interrupt 11
error_code_interrupt_handler    12      ; create handler for interrupt 12
error_code_interrupt_handler    13      ; create handler for interrupt 13
error_code_interrupt_handler    14      ; create handler for interrupt 14
no_error_code_interrupt_handler 15      ; create handler for interrupt 15
no_error_code_interrupt_handler 16      ; create handler for interrupt 16
error_code_interrupt_handler    17      ; create handler for interrupt 17
no_error_code_interrupt_handler 18      ; create handler for interrupt 18
no_error_code_interrupt_handler 19      ; create handler for interrupt 19
no_error_code_interrupt_handler 20      ; create handler for interrupt 20
