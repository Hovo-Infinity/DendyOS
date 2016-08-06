#include "console.h"

/*	Global Variables*/
char *framebuffer = (char *) 0x000B8000;
int current_col = 0;
int current_line = 0;

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

void nextcell()
{
    ++current_col;
    if (current_col == CONSOLE_WIDTH - 1)
    {
        newline();
    }
}

void newline()
{
    current_col = 0;
    ++current_line;
    if (current_line == CONSOLE_HEIGHT - 1)
    {
        current_line = 0;
    }
}

void print(const char *stringToWrite)
{
    int i;
    for ( i = 0
    	; stringToWrite[i] != '\0'
        ; ++i, nextcell() )
    {
        fb_write_cell(FBCHAR_SIZE * ( current_col + CONSOLE_WIDTH * current_line )
        	, stringToWrite[i]
        	, FB_BLACK
        	, FB_LIGHT_GREEN);
    }
}
