#include "log.h"

char log_buff[33];

void log_str(char *str, enum log_color policy)
{
  set_log_policy(policy);
  put_str(str);
}

void log_hex(unsigned int hex, enum log_color policy)
{
  set_log_policy(policy);
  uitoa(hex, 16, log_buff);
  put_str(log_buff);
}

void log_bin(unsigned int bin, enum log_color policy)
{
  set_log_policy(policy);
  uitoa(bin, 2, log_buff);
  put_str(log_buff);
}

void log_int(int integer, enum log_color policy)
{
  set_log_policy(policy);
  itoa(integer, 10, log_buff);
  put_str(log_buff);
}

void set_log_policy(enum log_color policy)
{
  enum fb_Color forecolor = FB_WHITE, backcolor = FB_BLACK;

  switch(policy) {
    case none:
      forecolor = FB_WHITE;
      backcolor = FB_BLACK;
      break;
    case information:
      forecolor = FB_LIGHT_CYAN;
      backcolor = FB_BLACK;
      break;
    case warning:
      forecolor = FB_LIGHT_MAGENTA;
      backcolor = FB_BLACK;
      break;
    case error:
      forecolor = FB_RED;
      backcolor = FB_BLACK;
      break;
    case critical:
      forecolor = FB_BLACK;
      backcolor = FB_RED;
      break;
    }

  set_text_color(forecolor, backcolor);
}
