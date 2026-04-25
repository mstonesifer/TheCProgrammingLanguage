#include <stdio.h>

/* k&r exercise 4-14 */

/* Define a macro `swap(t, x, y)` that interchanges
 * two arguments of type t. (Block structure will
 * help.)
 */

#define swap(t, x, y) { \
	t tmp; \
	tmp = x; \
	x = y; \
	y = tmp; \
}	

void main(void)
{
	int i, j;

	i = 1;
	j = 2;
	printf("i = %i\nj = %i\n", i, j);
	swap(int, i, j);
	puts("swapped");
	printf("i = %i\nj = %i\n", i, j);
}
