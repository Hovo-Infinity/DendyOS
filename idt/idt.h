#ifndef IDT_H
#define IDT_H

#include "handlers.h"
#include "../utility/utility.h"
#include "../console/console.h"


/* Defines an IDT entry */
struct idt_entry
{
  word offset_lo;
  word sel;			/* Our kernel segment goes here! */
  byte always0;		/* This will ALWAYS be set to 0! */
  byte flags;			/* Set using the above table! */
  word offset_hi;
} __attribute__((packed));

struct idt_ptr
{
  word limit;
  dword base;
} __attribute__((packed));

struct cpu_state {
  unsigned int eax;
  unsigned int ecx;
  unsigned int edx;
  unsigned int ebx;
  unsigned int esp;
  unsigned int ebp;
  unsigned int esi;
  unsigned int edi;
} __attribute__((packed));

struct stack_state {
  unsigned int error_code;
  unsigned int eip;
  unsigned int cs;
  unsigned int eflags;
} __attribute__((packed));

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack);

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256] __attribute__((aligned(0x1000)));
struct idt_ptr idtp __attribute__((aligned(0x10)));

/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load();
extern void handler_0();
extern void handler_3();

/* main usage */
void idt_install();

/* for special needs */
dword eax_shit;
dword cs_shit;

#endif /* IDT_H */
