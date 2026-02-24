#include <stdio.h>

/* create a word length histogram from an input */

#define OUT 0
#define IN 1

void main()
{
	// need to resolve what makes the end of a word
	
	int c, i, state, nchar = 0;
	int asize = 45;
	int wlen[asize];

	for (i = 0; i < asize; ++i)
		wlen[i] = 0;

	state = OUT;
	// get word lengths from input
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t' || c == ',') {
			if (nchar > asize)
				++wlen[0];
			else if (state == IN)
				++wlen[nchar];
			nchar = 0;
			state = OUT;
		} else {
			++nchar;
			state = IN;
		}
	}

	// print histogram
	for (i = 1; i < asize; ++i) {
		// skip where no words of that size
		if (wlen[i] < 1)
			continue;

		// print a bar for each word of that length
		printf("%3d ", i);
		for (int j = 0; j < wlen[i]; ++j)
			putchar('|');
		printf(" %d\n", wlen[i]);
	}

	// if any words with character count >45, print a bar for each
	if (wlen[0] > 0) {
		printf(">45 ");
		for (i = 0; i < wlen[0]; ++i)
			putchar('|');
	}
	putchar('\n');
}
