#include <stdio.h>

/* verify the expression getchar != EOF is 0 or 1 */

void main()
{
	int c;

	c = getchar() != EOF;

	printf("eof value: %d\n", c);
}
