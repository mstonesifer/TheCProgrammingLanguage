#include <stdio.h>

/* prints the first 80 ascii chars in a table */

#define START 33 /* ascii char to start with */
#define ROWS 20 /* how many chars to print in each column */
#define COLS 5 /* how many column sets to print horizontally */

void main()
{
	int i, j, end;

	// print header
	for (i = 0; i < COLS; ++i)
		printf("| ascii |   val ");
	printf("|\n");
	for (i = 0; i < COLS; ++i) 
		printf("|-------|-------");
	printf("|\n");


	// print values
	end = START + ROWS;
	for (i = START; i < end; ++i) {
		for (j = 0; j < COLS; ++j) {
			printf("|    ");
			putchar(i + (20 * j));
			printf("  |%6d ", i + (20 * j));
		}
		printf("|\n");
	}
}
