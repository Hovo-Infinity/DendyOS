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

global handler_0
handler_0:
no_error_code_interrupt_handler 0       ; create handler for interrupt 0
;handler_0 endp

global handler_1
handler_1:
no_error_code_interrupt_handler 1       ; create handler for interrupt 1
;handler_1 endp

global handler_2
handler_2:
no_error_code_interrupt_handler 2       ; create handler for interrupt 2
;handler_2 endp

global handler_3
handler_3:
no_error_code_interrupt_handler 3       ; create handler for interrupt 3
;handler_3 endp

global handler_4
handler_4:
no_error_code_interrupt_handler 4       ; create handler for interrupt 4
;handler_4 endp

global handler_5
handler_5:
no_error_code_interrupt_handler 5       ; create handler for interrupt 5
;handler_5 endp

global handler_6
handler_6:
no_error_code_interrupt_handler 6       ; create handler for interrupt 6
;handler_6 endp

global handler_7
handler_7:
no_error_code_interrupt_handler 7       ; create handler for interrupt 7
;handler_7 endp

global handler_8
handler_8:
error_code_interrupt_handler 8          ; create handler for interrupt 8
;handler_8 endp

global handler_9
handler_9:
no_error_code_interrupt_handler 9       ; create handler for interrupt 9
;handler_9 endp

global handler_10
handler_10:
no_error_code_interrupt_handler 10       ; create handler for interrupt 10
;handler_10 endp

global handler_11
handler_11:
no_error_code_interrupt_handler 11       ; create handler for interrupt 11
;handler_11 endp

global handler_12
handler_12:
no_error_code_interrupt_handler 12       ; create handler for interrupt 12
;handler_12 endp

global handler_13
handler_13:
no_error_code_interrupt_handler 13       ; create handler for interrupt 13
;handler_13 endp

global handler_14
handler_14:
no_error_code_interrupt_handler 14       ; create handler for interrupt 14
;handler_14 endp

global handler_15
handler_15:
no_error_code_interrupt_handler 15       ; create handler for interrupt 15
;handler_15 endp

global handler_16
handler_16:
no_error_code_interrupt_handler 16       ; create handler for interrupt 16
;handler_16 endp

global handler_17
handler_17:
error_code_interrupt_handler 17          ; create handler for interrupt 17
;handler_17 endp

global handler_18
handler_18:
no_error_code_interrupt_handler 18       ; create handler for interrupt 18
;handler_18 endp

global handler_19
handler_19:
no_error_code_interrupt_handler 19       ; create handler for interrupt 19
;handler_19 endp

global handler_20
handler_20:
no_error_code_interrupt_handler 20       ; create handler for interrupt 20
;handler_20 endp
