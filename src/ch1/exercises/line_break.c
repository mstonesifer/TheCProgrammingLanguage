#include <stdio.h>

/* prints an input one word per line */

void main()
{
	int c, pc;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t' || c == ',') {
			// only newline if the prev char not a newline
			if (pc != '\n') {
				putchar('\n');
				pc = '\n';
			}
		}
		else {
			putchar(c);
			pc = c;
		}
	}
	putchar('\n');
}
