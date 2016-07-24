#include "console.h"

/*	Global Variables*/
char *framebuffer = (char *) 0x000B8000;
int fb_iterator = 0;

inline void fb_write_cell(unsigned int location
	, char character
	, unsigned char fg_color
	, unsigned char bg_color)
{
    framebuffer[location] = character;
    framebuffer[location + 1] = \
    		((fg_color & 0x0F) << 4) | (bg_color & 0x0F);
}

void clear_screen()
{
    int i;
    for ( i = 0
    	; i < CONSOLE_WIDTH * CONSOLE_HEIGHT * FBCHAR_SIZE
    	; ++i )
    {
        framebuffer[i]=0;
    }
}

void newline()
{
    fb_iterator += CONSOLE_HEIGHT;
}

void print(const char *stringToWrite)
{
    int i;
    for ( i = 0
    	; stringToWrite[i] != '\0'
    	; ++i, ++fb_iterator )
    {
        fb_write_cell(FBCHAR_SIZE * fb_iterator
        	, stringToWrite[i]
        	, FB_BLACK
        	, FB_LIGHT_GREEN);
    }
}