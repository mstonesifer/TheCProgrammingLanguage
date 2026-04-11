#include <stdio.h>

/* k&r exercise 2-8 */

/* prototypes */
int rightrot(int x, int n);
int bitcount(unsigned int);

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
	int z = bitcount(~0);			// int size
	return (x >> n) | (b << ( - n));	// rotate and restore
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned int x)
{
	int b = 0;
	
	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;
	return b;
}
