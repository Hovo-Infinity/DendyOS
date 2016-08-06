#ifndef UTILITY_H
#define UTILITY_H

/* global data structures */
typedef unsigned int dword;
typedef unsigned short word;
typedef unsigned char byte;

/* functions below are used inside a global scope*/
/* mainly write your utility functions here */
unsigned int strlen(byte *stringGiven);
void memcpy(byte *source, byte *dest, word length);
void memset(byte *address, byte symbol, dword size);
void memsetw(word *address, word symbol, dword size);
void hextochar(char *pIn, char *pOut, int pLen);
void chartohex(char *pIn,char *pOut,int pLen);

#endif
