#ifndef KMAIN_H
#define KMAIN_H

/* Additional dependencies */
#include "../../utility/utility.h"
#include "../../console/console.h"
#include "../../gdt/gdt.h"
#include "../../idt/idt.h"

char HelloMsg[] = "Hello World!\n\r";

/* The kernel starts executing here */
void kmain();

#endif /* KMAIN_H */
