#ifndef CONSOLE_H
#define CONSOLE_H

#include "../utility/utility.h"
#include "../io/io.h"

/*  Constants and magic numbers */
#define CONSOLE_WIDTH	80
#define CONSOLE_HEIGHT	25
#define FBCHAR_SIZE 2

/* Color convensions of frame buffer */
enum fb_Color {
  FB_BLACK,
  FB_BLUE,
  FB_GREEN,
  FB_CYAN,
  FB_RED,
  FB_MAGENTA,
  FB_BROWN,
  FB_LIGHT_GREY,
  FB_DARK_GREY,
  FB_LIGHT_BLUE,
  FB_LIGHT_GREEN,
  FB_LIGHT_CYAN,
  FB_LIGHT_RED,
  FB_LIGHT_MAGENTA,
  FB_LIGHT_BROWN,
  FB_WHITE
};

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 */
void clear_screen(void);
void move_csr(void);
void scroll(void);
void put_char(unsigned char c);
void put_str(char *text);
void set_text_color(enum fb_Color forecolor, enum fb_Color backcolor);

#endif /* CONSOLE_H */
