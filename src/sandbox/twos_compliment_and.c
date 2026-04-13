#include <stdio.h>

int main(void)
{
	int x = 64;

	printf("%d &= (%d - 1) => ", x, x);
	printf("%d\n", x &= (x - 1));

	int y = 17;
	int shift = 5;
	printf("%i %b << %i = %i, %b\n", y, y, shift, y << shift, y << shift);
	printf("%i %b << %i = %i, %b\n", y, y, -shift, y << -shift, y << -shift);
	printf("%i %b >> %i = %i, %b\n", y, y, shift, y >> shift, y >> shift);
	printf("%i %b >> %i = %i, %b\n", y, y, -shift, y >> -shift, y >> -shift);
}
