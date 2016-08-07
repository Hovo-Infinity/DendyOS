#include "kmain.h"

void kmain()
{
  gdt_install();
  idt_install();
  put_str(HelloMsg);
  __asm__ ("int $3");
  __asm__ ("int $3");
  int x = 5, y = 0;

  x /= y;
}
