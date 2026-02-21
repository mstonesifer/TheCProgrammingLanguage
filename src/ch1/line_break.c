#include <stdio.h>

#define IN 1	/* inside a word */
#define OUT 0	/* outside a word */

/* prints an input one word per line */

void main()
{
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF) {
		if (state == OUT) {
			state = IN;
			putchar(c);
		}
		else if (c == '\n')
			putchar(c);
		else if (c == ' ' || c == '\t' || c == ',') {
			putchar('\n');
			state = OUT;
		}
		else
			putchar(c);
	}
	putchar('\n');
}
