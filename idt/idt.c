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

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack)
{
  switch (interrupt)
    {
    case 0:
      division_by_zero_handler();
      break;
    case 3:
      breakpoint_interrupt_handler();
      break;
    }
  eax_shit = cpu.eax;
  cs_shit = stack.cs;
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
  idt_set_gate(3, (dword)&handler_3, 0x08, 0xEE);

  /* Points the processor's internal register to the new IDT */
  idt_load();
}
