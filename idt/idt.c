#include "idt.h"

void idt_set_gate(unsigned char num
            , unsigned long handler
            , unsigned short sel
            , unsigned char flags)
{
    /* Setup the offset of interrupt handler */
    idt[num].offset_lo = (handler & 0xFFFF);
    idt[num].offset_hi = (handler >> 16);

    /* Setup the descriptor limits */
    idt[num].sel = (sel & 0xFFFF);

    /* Setup flags  |P|DPL|0|D|1 1 0| */
    idt[num].flags = flags;

    /* Setup defaults */
    idt[num].always0 = 0x00;

}

void handler_0( dword error_code
                , dword eip)
{
    __asm__("cli");
    char error_code_str[10];
    char eip_str[10];

    itoa(error_code, 16, error_code_str);

    itoa(eip, 16, eip_str);
    print(eip_str);
    newline();

/*
    itoa(eip, 16, eip_str);
    print(eip_str);

    itoa(cs, 16, cs_str);
    print(cs_str);

    itoa(eflags, 16, eflags_str);
    print(eflags_str);
    */
}


/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (dword)&idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset((unsigned char *)&idt, 0, (sizeof(struct idt_entry) * 256));

    /* Add any new ISRs to the IDT here using idt_set_gate */
    idt_set_gate(0, (dword)&handler_0, 0x08, 0xEE);

    /* Points the processor's internal register to the new IDT */
    idt_load();
}