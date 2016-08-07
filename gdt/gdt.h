#ifndef GDT_H
#define GDT_H

#include "../utility/utility.h"

/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
struct gdt_entry {
  word limit_low;
  word base_low;
  byte base_middle;
  byte access;
  byte attributes;
  byte base_high;
} __attribute__((packed));

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr {
  word limit;
  dword base;
} __attribute__((packed));

/* Our GDT, with 3 entries, and finally our special GDT pointer */
struct gdt_entry gdt[3] __attribute__((aligned(0x1000)));
struct gdt_ptr gp __attribute__((aligned(0x10)));


/* This will be a function in loader.s. We use this to properly
*  reload the new segment registers */
extern void gdt_flush();

/* use this function in your code */
void gdt_install();

#endif /* GDT_H */
