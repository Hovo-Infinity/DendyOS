#ifndef UTILITY_H
#define UTILITY_H

/* global data structures */
typedef unsigned int dword;
typedef unsigned short word;
typedef unsigned char byte;

/* functions below are used inside a global scope*/
/* mainly write your utility functions here */
unsigned int strlen(const char *stringGiven);
void memset(unsigned char *address, unsigned char symbol, unsigned long size);
void itoa(unsigned int integerPassed, unsigned int baseSystem, char *outputBuffer);

#endif