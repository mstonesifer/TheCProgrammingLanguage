#include <stdio.h>

/* copies an input to an output, replacing tabs with '\t', backspaces with '\b'
 * and backslashes with '\\', making tabs and backspaces visible in an
 * unambigous way.
 */

void main()
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			putchar('t');
		}
		else if (c == '\b') {
			putchar('\\');
			putchar('b');
		}
		else if (c == '\\') {
			putchar('\\');
			putchar('\\');
		}
		else
			putchar(c);
	}
}
