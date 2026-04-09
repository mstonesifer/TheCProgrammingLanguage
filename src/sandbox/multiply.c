#include <stdio.h>

int main(void)
{
	int a = 2;
	while(a < 256) {
		a *= 2;
		printf("a be %i\n", a);
	}
	putchar('\n');
}
