#include <stdio.h>

/* copy input to the output, replacing each string of blanks with a single blank */

#define EMPTY ''

void main()
{
	int currChar, prevChar = 0;

	while ((currChar = getchar()) != EOF) {
		if (currChar != ' ' || prevChar != ' ')
			putchar(currChar);
		
		prevChar = currChar;
	}
}
