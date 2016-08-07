#include "idt.h"

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries here, the rest exists as a bit of a trap.
*  If any undefined IDT entry is hit, it normally will cause an
*  "Unhandled Interrupt" exception. Any descriptor for which
*  the 'presence' bit is cleared (0) will generate an "Unhandled
*  Interrupt" exception */
struct idt_entry idt[256] __attribute__((aligned(0x1000)));
struct idt_ptr idtp __attribute__((aligned(0x10)));

/* for logging unhandled exceptions */
struct cpu_state last_cpu_state;
struct stack_state last_stack_state;

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
  last_cpu_state = cpu;
  last_stack_state = stack;
  switch (interrupt) {
    case 0:
      division_by_zero_handler();
      stack.eip = (dword)&unhandled_exception_handler;
      break;
    case 3:
      breakpoint_interrupt_handler();
      break;
    }
}

void unhandled_exception_handler()
{
  log_str("Unhandled exception occurred!\n\n", error);
  log_str("CPU state:\n", information);
  log_str("EAX = ", information);
  log_hex(last_cpu_state.eax, warning);
  log_str(" ECX = ", information);
  log_hex(last_cpu_state.ecx, warning);
  log_str(" EDX = ", information);
  log_hex(last_cpu_state.edx, warning);
  log_str(" EBX = ", information);
  log_hex(last_cpu_state.ebx, warning);
  log_str("\nESP = ", information);
  log_hex(last_cpu_state.esp, warning);
  log_str(" EBP = ", information);
  log_int(last_cpu_state.ebp, warning);
  log_str(" ESI = ", information);
  log_hex(last_cpu_state.esi, warning);
  log_str(" EDI = ", information);
  log_hex(last_cpu_state.edi, warning);
  log_str("\n\nStack state:\n", information);
  log_str("Error code: ", information);
  log_hex(last_stack_state.error_code, warning);
  log_str(" EIP = ", information);
  log_hex(last_stack_state.eip, warning);
  log_str(" CS = ", information);
  log_bin(last_stack_state.cs, warning);
  /*log_str(" EFLAGS = ", information);
  log_bin(last_stack_state.eflags, warning);*/
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
