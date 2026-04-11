#include <stdio.h>

/* k&r exercise 2-7 */

/* prototypes */
unsigned invert(unsigned x, int p, int n);

int main(void)
{
	unsigned x = 0x99;			// 153 in decimal => 10011001 binary
	int p = 4;
	int n = 5;
	int e = 0b10000110;
	printf("x start:  %3i %8b\n", x, x);
	x = invert(x, p, n);
	printf("Expected: %3i %8b\n", e, e);
	printf("Actual:   %3i %8b\n", x, x);
}

/* invert: inverts n bits in x that begin at position p; returns x */
unsigned invert(unsigned x, int p, int n)
{
	unsigned int t = p + 1 - n;		// target bits to set
	unsigned int m_x = ~(~0 << n) << t;	// bit mask for x

	return x ^ m_x;				// XOR target bits
}

