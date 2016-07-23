#include "kmain.h"

inline void fb_write_cell(unsigned int location, 
    char character, 
    unsigned char fg_color, 
    unsigned char bg_color)
{
    framebuffer[location] = character;
    framebuffer[location + 1] = ((fg_color & 0x0F) << 4) | (bg_color & 0x0F);
}

void clear_screen(void)
{
    int i;
    for ( i = 0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT * FBCHAR_SIZE ; ++i )
    {
        framebuffer[i]=0;
    }
} 

void print(const char *stringToWrite)
{
    int i;
    static int fb_iterator = 0;
    for ( i = 0 ; stringToWrite[i] != '\0' ; ++i, ++fb_iterator )
    {
        fb_write_cell(FBCHAR_SIZE * fb_iterator, stringToWrite[i], FB_BLACK, FB_WHITE);
    }
}

int kmain(int arg1, int arg2, int arg3)
{
    char hellostring[10];
    itoa(-1, 16, hellostring);
    print(hellostring);
    gdt_install();
    idt_install();
    return arg1 + arg3 + arg2;
}