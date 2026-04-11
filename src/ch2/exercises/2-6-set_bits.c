#include <stdio.h>

/* k&r exercise 2-6 */

/* prototypes */
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void)
{
	unsigned x = 0x99;			// 153 in decimal => 10011001 binary
	int y = 06;				// 6   in decimal => 00000110 binary
	int p = 6;
	int n = 3;
	printf("x start:  %3i %8b\n", x, x);
	printf("y start:  %3i %8b\n", y, y);
	x = setbits(x, p, n, y);
	printf("Expected: 233 %8b\n", 233);	// 233 => 11101001 binary
	printf("Actual:   %3i %8b\n", x, x);

	x = 67;					// 01000011
	y = 132;				// 10000100
	p = 4;
	n = 2;
	printf("x start:  %3i %8b\n", x, x);
	printf("y start:  %3i %8b\n", y, y);
	x = setbits(x, p, n, y);
	printf("Expected:  67 %8b\n", 67);	// 01000011
	printf("Actual:   %3i %8b\n", x, x);

	x = 133;				// 10000101
	y = 207;				// 11001111
	p = 1;
	n = 1;
	printf("x start:  %3i %8b\n", x, x);
	printf("y start:  %3i %8b\n", y, y);
	x = setbits(x, p, n, y);
	printf("Expected: 135 %8b\n", 135);	// 10000111
	printf("Actual:   %3i %8b\n", x, x);
	
	x = 317;				// 00000001 00111101
	y = 1987;				// 00000111 11000011
	p = 12;					// 00000001 10000000
	n = 6;					// 00000000 00000011
	printf("x start:  %4i %16b\n", x, x);
	printf("y start:  %4i %16b\n", y, y);
	x = setbits(x, p, n, y);
	printf("Expected: %4i %16b\n", 0b0000000110111101, 0b0000000110111101);
	printf("Actual:   %4i %16b\n", x, x);

}

/* setbits: sets the n bits of x beginning at position p to
 * the rightmost n bits of y; returns x */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned int t = p + 1 - n;		// target bits to set
	unsigned int m_x = ~(~(~0 << n) << t);	// bit mask for x
	unsigned int m_y = ~(~0 << n);		// bit mask for y	

	return (x & m_x) | ((y & m_y) << t);
}

