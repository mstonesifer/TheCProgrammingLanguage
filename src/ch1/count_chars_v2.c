#include <stdio.h>

/* count blanks, tabs, and newlines of an input */

void main()
{
	int c;
	int blankCount = 0, tabCount = 0, newlineCount = 0;

	for (c = 0; (c = getchar()) != EOF; ++c) {
		if (c == ' ')
			++blankCount;
		if (c == '\t')
			++tabCount;
		if (c == '\n')
			++newlineCount;
	}

	printf("blank space count: %d\n", blankCount);
	printf("tab count: %d\n", tabCount);
	printf("new line count: %d\n", newlineCount);
}
