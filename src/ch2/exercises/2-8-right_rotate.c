#include <stdio.h>

/* k&r exercise 2-8 */

/* prototypes */
int rightrot(int x, int n);
int count_bits(unsigned int);

int main(void)
{
	int x = 0x99;			// 153 in decimal => 10011001 binary
	int n = 5;
	int e = 0b11001000000000000000000000000100;
	printf("x start:  %12i %32b\n", x, x);
	x = rightrot(x, n);
	printf("Expected: %12i %32b\n", e, e);
	printf("Actual:   %12i %32b\n", x, x);
}

/* rightrot: inverts n bits in x that begin at position p; returns x */
int rightrot(int x, int n)
{
	int m_x = ~(~0 << n);			// bit mask for x
	int b = x & m_x;			// buffer to store bits before rotate
	int z = count_bits(~0);			// int size
	return (x >> n) | (b << ( - n));	// rotate and restore
}

int count_bits(unsigned int n)
{
	int c = 0;
	while (n) {
		c += n % 2;
		n >>= 1;
	}
	return c;
}
