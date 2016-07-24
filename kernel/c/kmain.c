#include "kmain.h"

void kmain()
{
	int x = 5;
	int y = 0;

    gdt_install();
    idt_install();
    
    /*print(HelloMsg);*/

    x /= y;
}