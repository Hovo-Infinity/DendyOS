#ifndef LOG_H
#define LOG_H

#include "console.h"

enum log_color {
  none,
  information,
  warning,
  error,
  critical
};

void log_str(char *str, enum log_color policy);
void log_hex(unsigned int hex, enum log_color policy);
void log_bin(unsigned int bin, enum log_color policy);
void log_int(int integer, enum log_color policy);
void set_log_policy(enum log_color policy);

#endif /* LOG_H */
