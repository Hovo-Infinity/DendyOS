#ifndef IDT_H
#define IDT_H

#include "handlers.h"
#include "../utility/utility.h"
#include "../console/log.h"

/* Defines an IDT entry */
struct idt_entry {
  word offset_lo;
  word sel;                     /* Our kernel segment goes here! */
  byte always0;                 /* This will ALWAYS be set to 0! */
  byte flags;                   /* Set using the above table! */
  word offset_hi;
} __attribute__((packed));

struct idt_ptr {
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

void interrupt_handler(struct cpu_state cpu
                       , unsigned int interrupt
                       , struct stack_state stack);

void unhandled_exception_handler();

/* This exists in 'loader.asm', and is used to load our IDT */
extern void idt_load();
extern void handler_0();
extern void handler_1();
extern void handler_2();
extern void handler_3();
extern void handler_4();
extern void handler_5();
extern void handler_6();
extern void handler_7();
extern void handler_8();
extern void handler_9();
extern void handler_10();
extern void handler_11();
extern void handler_12();
extern void handler_13();
extern void handler_14();
extern void handler_15();
extern void handler_16();
extern void handler_17();
extern void handler_18();
extern void handler_19();
extern void handler_20();

/* main usage */
void idt_install();

#endif /* IDT_H */
