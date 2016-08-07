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

void interrupt_handler(struct cpu_state cpu
                       , unsigned int interrupt
                       , struct stack_state stack)
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
  eax_ = cpu.eax;
  cs_ = stack.cs;
}

/* Installs the IDT */
void idt_install()
{
  /* Sets the special IDT pointer up, just like in 'gdt.c' */
  idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
  idtp.base = (dword)&idt;

  /* Clear out the entire IDT, initializing it to zeros */
  memset((unsigned char *)&idt, 0, (sizeof(struct idt_entry) * 256));

  /* ISRs to the IDT here using idt_set_gate */
  idt_set_gate(0, (dword)&handler_0, 0x08, 0xEE);
  idt_set_gate(1, (dword)&handler_1, 0x08, 0xEE);
  idt_set_gate(2, (dword)&handler_2, 0x08, 0xEE);
  idt_set_gate(3, (dword)&handler_3, 0x08, 0xEE);
  idt_set_gate(4, (dword)&handler_4, 0x08, 0xEE);
  idt_set_gate(5, (dword)&handler_5, 0x08, 0xEE);
  idt_set_gate(6, (dword)&handler_6, 0x08, 0xEE);
  idt_set_gate(7, (dword)&handler_7, 0x08, 0xEE);
  idt_set_gate(8, (dword)&handler_8, 0x08, 0xEE);
  idt_set_gate(9, (dword)&handler_9, 0x08, 0xEE);
  idt_set_gate(10, (dword)&handler_10, 0x08, 0xEE);
  idt_set_gate(11, (dword)&handler_11, 0x08, 0xEE);
  idt_set_gate(12, (dword)&handler_12, 0x08, 0xEE);
  idt_set_gate(13, (dword)&handler_13, 0x08, 0xEE);
  idt_set_gate(14, (dword)&handler_14, 0x08, 0xEE);
  idt_set_gate(15, (dword)&handler_15, 0x08, 0xEE);
  idt_set_gate(16, (dword)&handler_16, 0x08, 0xEE);
  idt_set_gate(17, (dword)&handler_17, 0x08, 0xEE);
  idt_set_gate(18, (dword)&handler_18, 0x08, 0xEE);
  idt_set_gate(19, (dword)&handler_19, 0x08, 0xEE);
  idt_set_gate(20, (dword)&handler_20, 0x08, 0xEE);

  /* Points the processor's internal register to the new IDT */
  idt_load();
}
