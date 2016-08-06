#include "utility.h"

unsigned int strlen(byte *stringGiven)
{
  unsigned int i;
  for ( i = 0; stringGiven[i] != '\0'; ++i);
  return i;
}

void memset(byte *address, byte symbol, dword size)
{
  unsigned int i;
  for( i = 0; i < size; ++i)
    {
      address[i] = symbol;
    }
}


void memcpy(byte *source, byte *dest, word length)
{
  unsigned int i;
  for(i = 0; i < length; ++i)
    {
      dest[i] = source[i];
    }
}

void hextochar(char *pIn, char *pOut, int pLen)
{
  int i, j;
  char hex;
  for( i = 0, j = 0; i < pLen; ++i, ++j)
    {
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
  for( i = 0, j = 0; i < pLen; ++i, ++j)
    {
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

void memsetw(word *address, word symbol, dword size)
{
  unsigned int i;
  for( i = 0; i < size; ++i)
    {
      address[i] = symbol;
    }
}
