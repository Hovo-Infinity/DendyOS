#include "utility.h"

unsigned int strlen(const char *stringGiven)
{
    unsigned int i;
    for ( i = 0; stringGiven[i] != '\0'; ++i);
    return i;
}

void memset(unsigned char *address, unsigned char symbol, unsigned long size)
{
	unsigned int i;
	for( i = 0; i < size; ++i)
	{
		address[i] = symbol;
	}
}

void itoa(unsigned int integerPassed, unsigned int baseSystem, char *outputBuffer)
{
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int maxIntegerLength = 8;
    
    char *ptr = outputBuffer;

    ptr += maxIntegerLength;
    *ptr = '\0';
    --ptr;

    while( maxIntegerLength != 0 )
    {
        *ptr = digits[ integerPassed % baseSystem ];
        integerPassed /= baseSystem;
        --ptr;
        --maxIntegerLength;
    }
}