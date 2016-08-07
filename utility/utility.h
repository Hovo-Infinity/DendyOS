#ifndef UTILITY_H
#define UTILITY_H

/* global data structures */
typedef unsigned int dword;
typedef unsigned short word;
typedef unsigned char byte;

/* functions below are used inside a global scope*/
/* mainly write your utility functions here */
int strlen(const char *str);
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
unsigned char *memset(unsigned char *dest, unsigned char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
void hextochar(char *pIn, char *pOut, int pLen);
void chartohex(char *pIn,char *pOut,int pLen);
void uitoa(unsigned int integer, char base, char* output);
void itoa(int integer, char base, char* output);
void strrev(char* str, int length);
#endif
