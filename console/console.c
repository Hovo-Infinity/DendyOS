#include "console.h"

/*	Global Variables*/
byte *framebuffer = (byte *) 0x000B8000;
enum fb_Color attrib = FB_WHITE;
int csr_x = 0, csr_y = 0;

/* Clears the screen */
void clear_screen(void)
{
  word blank;

  /* Again, we need the 'short' that will be used to
    *  represent a space with color */
  blank = 0x20 | (attrib << 8);

  /* Sets the entire screen to spaces in our current
    *  color */
  memsetw ( (word*)framebuffer, blank, CONSOLE_WIDTH * CONSOLE_HEIGHT);

  /* Update out virtual cursor, and then move the
    *  hardware cursor */
  csr_x = 0;
  csr_y = 0;
  move_csr();
}

/* Scrolls the screen */
void scroll(void)
{
  unsigned blank, temp;

  /* A blank is defined as a space... we need to give it
    *  backcolor too */
  blank = 0x20 | (attrib << 8);

  /* Row 25 is the end, this means we need to scroll up */
  if(csr_y >= CONSOLE_HEIGHT)
    {
      /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
      temp = csr_y - CONSOLE_HEIGHT + 1;
      memcpy (framebuffer
              , framebuffer + temp * CONSOLE_WIDTH
              , (CONSOLE_HEIGHT - temp) * CONSOLE_WIDTH * 2);

      /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
      memset (framebuffer + (CONSOLE_HEIGHT - temp) * CONSOLE_WIDTH
              , blank
              , CONSOLE_WIDTH);
      csr_y = CONSOLE_HEIGHT - 1;
    }
}

/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
void move_csr(void)
{
  unsigned temp;

  /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
  temp = csr_y * CONSOLE_WIDTH + csr_x;

  /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
  outb(0x3D4, 14);
  outb(0x3D5, temp >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, temp);
}

/* Puts a single character on the screen */
void put_char(word c)
{
  word *where;
  dword att = attrib << 8;

  /* Handle a backspace, by moving the cursor back one space */
  if(c == 0x08)
    {
      if(csr_x != 0) --csr_x;
    }
  /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
  else if(c == 0x09)
    {
      csr_x = (csr_x + 8) & ~(8 - 1);
    }
  /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
  else if(c == '\r')
    {
      csr_x = 0;
    }
  /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
  else if(c == '\n')
    {
      csr_x = 0;
      ++csr_y;
    }
  /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
  else if(c >= ' ')
    {
      where = (word*)framebuffer + (csr_y * CONSOLE_WIDTH + csr_x);
      *where = c | att;	/* Character AND attributes: color */
      ++csr_x;
    }

  /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
  if(csr_x >= CONSOLE_WIDTH)
    {
      csr_x = 0;
      ++csr_y;
    }

  /* Scroll the screen if needed, and finally move the cursor */
  scroll();
  move_csr();
}

/* Uses the above routine to output a string... */
void put_str(char *text)
{
  while(*text)
    put_char(*text++);
}

/* Sets the forecolor and backcolor that we will use */
void set_text_color(enum fb_Color forecolor, enum fb_Color backcolor)
{
  /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
  attrib = (backcolor << 4) | (forecolor & 0x0F);
}
