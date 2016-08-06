#include "kmain.h"

void kmain()
{
  /*int x = 5, y = 0;*/


  gdt_install();
  idt_install();

  put_str((byte*)HelloMsg);
}
