#include "io.h"

/* COLORS */
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

struct example {
    unsigned char config;   /* bit 0 - 7   */
    unsigned short address; /* bit 8 - 23  */
    unsigned char index;    /* bit 24 - 31 */
} __attribute__((packed));

/*	Global Variables*/
char *fb = (char *) 0x000B8000;
char HelloMsg[] = "Hello World!";

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
inline void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void clear_screen(void) {
	int i;
	for(i=0;i<80*25*2;i++) fb[i]=0;
}

void write_string(char *A) {
	int i;
	for(i=0;A[i];i++) fb_write_cell(2*i, A[i], FB_BLACK, (i+1)%16);
}

/* The C function */
int kmain(int arg1, int arg2, int arg3) {

	write_string(HelloMsg);
    return arg1 + arg2 + arg3;
}