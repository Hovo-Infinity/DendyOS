#ifndef KMAIN_H
#define KMAIN_H

/* Additional dependencies */
#include "../../gdt/gdt.h"

/*  Constants and magic numbers */
#define CONSOLE_WIDTH	85
#define CONSOLE_HEIGHT	25
#define FBCHAR_SIZE		2

/* Color convensions of frame buffer */
#define FB_BLACK			0
#define FB_BLUE				1
#define FB_GREEN			2
#define FB_CYAN				3
#define FB_RED				4
#define FB_MAGENTA			5
#define FB_BROWN			6
#define FB_LIGHT_GREY		7
#define FB_DARK_GREY		8
#define FB_LIGHT_BLUE		9
#define FB_LIGHT_GREEN		10
#define FB_LIGHT_CYAN		11
#define FB_LIGHT_RED		12
#define FB_LIGHT_MAGENTA	13
#define FB_LIGHT_BROWN		14
#define FB_WHITE			15

/*	Global Variables*/
char *framebuffer = (char *) 0x000B8000;
char HelloMsg[] = "Hello World!";


/* functions forward declarations */

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 */
inline void fb_write_cell(unsigned int location, char character, unsigned char fg_color, unsigned char bg_color);

void clear_screen(void);

void print(const char *stringToWrite);

unsigned int strlen(const char *stringGiven);

void itoa(unsigned int integerPassed, unsigned int baseSystem, char *outputBuffer);

/* The kernel starts executing here */
int kmain(int arg1, int arg2, int arg3);

#endif