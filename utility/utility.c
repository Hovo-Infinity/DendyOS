#include "utility.h"

int strlen(const char *str)
{
  int i = 0;
  while(str[i++]);
  return i;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
  int i;
  for(i = 0; i < count; ++i) {
      dest[i] = val;
    }
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
  int i;
  for( i = 0; i < count; ++i) {
      dest[i] = val;
    }
  return dest;
}

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
  int i;
  for(i = 0; i < count; ++i) {
      dest[i] = src[i];
    }
  return dest;
}

void hextochar(char *pIn, char *pOut, int pLen)
{
  int i, j;
  char hex;
  for(i = 0, j = 0; i < pLen; ++i, ++j) {
      hex = pIn[i];
      if ((hex >> 4) <= 9)
        pOut[j] = (hex >> 4) + '0';
      else
        pOut[j] = (hex >> 4) + '7';
      j++;
      if((hex & 0x0F) <= 9)
        pOut[j] = (hex & 0x0F) + '0';
      else
        pOut[j] = (hex & 0x0F) + '7';
    }
}

void chartohex(char *pIn, char *pOut, int pLen)
{
  int i,j;
  char tmp;
  for(i = 0, j = 0; i < pLen; ++i, ++j) {
      tmp = 0;
      if (pIn[i] >= '0' && pIn[i] <= '9')
        tmp |= pIn[i] - '0';
      else if (pIn[i] >= 'A' && pIn[i] <= 'F')
        tmp |= pIn[i] - '7';
      tmp <<= 4;
      i++;
      if (pIn[i] >= '0' && pIn[i] <= '9')
        tmp |= pIn[i] - '0';
      else if (pIn[i] >= 'A' && pIn[i] <= 'F')
        tmp |= pIn[i] - '7';
      pOut[j] = tmp;
    }
}

void uitoa(unsigned int integer, char base, char* output)
{
  if(!integer) {
      *output++ = '0';
      *output = '\0';
      return;
    }

  int i;
  char current_digit;

  for(i = 0; integer; ++i, integer /= base) {
      current_digit = integer % base;
      output[i] = current_digit + '0';
      if (current_digit > 9)
        output[i] += 7;
    }
  output[i] = '\0';

  strrev(output, i);
}

void itoa(int integer, char base, char* output)
{
  if (integer < 0) {
      *output++ = '-';
      integer = -integer;
    }

  uitoa(integer, base, output);
}

void strrev(char* str, int length)
{
  int i;
  for(i = 0; i < (length >> 1); ++i) {
      str[i] ^= str[length - i - 1];
      str[length - i - 1] ^= str[i];
      str[i] ^= str[length - i - 1];
    }
}
