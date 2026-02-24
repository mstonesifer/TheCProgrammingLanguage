#include <stdio.h>

/* create a character frequency histogram from an input */

#define SIZE 128 /* size of character set to track */
#define WEIGHT 4 /* how many instances before a bar is printed */

void main()
{
	int c, i, j;
	int oobcount = 0;
	int ccount[SIZE];

	for (i = 0; i < SIZE; ++i)
		ccount[i] = 0;

	// get char freq from input
	while ((c = getchar()) != EOF) {
		if (c > SIZE)
			++oobcount;
		else 
			++ccount[c];
	}

	// print histogram
	for (i = 0; i < SIZE; ++i) {
		// skip where no char instances
		if (ccount[i] < 1)
			continue;

		// print a bar for each word of that length
		putchar(i);
		putchar(' ');
		//printf("%3d ", i);
		for (int j = 0; j < ccount[i]; ++j)
			if ( j % WEIGHT == 0)
				putchar('|');

		printf(" %d\n", ccount[i]);
	}

	// if any out of bounds chars, print total
	if (oobcount > 0) {
		printf("oob ");
		for (i = 0; i < oobcount; ++i)
			if (oobcount % WEIGHT == 0)
				putchar('|');
		printf(" %d", oobcount);
	}
	putchar('\n');
}
