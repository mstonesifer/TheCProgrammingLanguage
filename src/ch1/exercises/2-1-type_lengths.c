#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <cs50.h>

void print_header(char s[]);
void print_from_header_files();
void print_char(int count, char c);
void print_from_calculated();

/* print the ranges for char, short, int and long, both signed and unsigned */
int main(void)
{
	

	string title = "Header file vals";
	print_header(title);
	print_from_header_files();
	putchar('\n');
	
	title = "Calculated";
	print_header(title);
	print_from_calculated();	
	putchar('\n');
}

/* prints table header with a char array as the title */
void print_header(char s[])
{
	printf("%s\n", s);
	print_char(57, '-');
	putchar('\n');
	printf("| type\t|");
	print_char(10, ' ');
	printf("min");
	print_char(10, ' ');
	putchar('|');
	print_char(10, ' ');
	printf("max");
	print_char(10, ' ');
	putchar('|');
	putchar('\n');
	print_char(57, '-');
	putchar('\n');
}

/* prints table with values from header files */
void print_from_header_files()
{
	printf("| char\t|%22i |%22i |\n", CHAR_MIN, CHAR_MAX);
	printf("| uchar\t|%22i |%22u |\n", 0, UCHAR_MAX);
	printf("| short\t|%22i |%22i |\n", SHRT_MIN, SHRT_MAX);
	printf("| ushrt\t|%22i |%22u |\n", 0, USHRT_MAX);
	printf("| int\t|%22i |%22i |\n", INT_MIN, INT_MAX);
	printf("| uint\t|%22i |%22u |\n", 0, UINT_MAX);
	printf("| long\t|%22ld |%22ld |\n", LONG_MIN, LONG_MAX);
	printf("| ulong\t|%22i |%22lu |\n", 0, ULONG_MAX);

	printf("| float\t|%22f |%22f |\n", FLT_MIN, FLT_MAX);
	printf("| dbl\t|%22f |%22f |\n", DBL_MIN, DBL_MAX);
}

/* prints table with calculated values */
void print_from_calculated()
{
	
	char c, cmax;
	for (c = 1; c > 0; ++c) {
		if (c > 0)
			cmax = c;
	}

	printf("| char\t|%22i |%22i |\n", c, cmax);

	unsigned char uc, ucmax;
	for (uc = 1; uc != 0; ++uc) {
		if (uc != 0)
			ucmax = uc;
	}

	printf("| uchar\t|%22i |%22u |\n", uc, ucmax);

	short s, smax;
	for (s = 1; s > 0; ++s) {
		if (s > 0)
			smax = s;
	}
	printf("| short\t|%22i |%22i |\n", s, smax);
	
	unsigned short us, usmax;
	for (us = 1; us > 0; ++us) {
		if (us > 0)
			usmax = us;
	}
	printf("| ushrt\t|%22i |%22u |\n", us, usmax);
	
	int i = 2;
	int imax = 0;
	while (i > 0) {
		i *= 2;
		if (i < 0)
			imax = i - 1;
	}
	printf("| int\t|%22i |%22i |\n", i, imax);

	unsigned int uimax = 0 - 1;
	printf("| uint\t|%22i |%22u |\n", 0, uimax);
	
	long l = 2;
	long lmax = 0;
	while (l > 0) {
		l *= 2;
		if (l < 0)
			lmax = l - 1;
	}
	printf("| long\t|%22ld |%22ld |\n", l, lmax);
	
	unsigned long ulmax = 0 - 1;
	printf("| ulong\t|%22i |%22lu |\n", 0, ulmax);

	float f = 0.0;
	float fmax = 0.0 - 1.0;
	printf("| float\t|%22f |%22f |\n", f, fmax);
}


/* prints param c count number of times */
void print_char(int count, char c)
{
	for (int i = 0; i < count; ++i)
		putchar(c);
}
