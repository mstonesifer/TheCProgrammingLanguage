#include <stdio.h>
#include "varnames.h"

static int BUF = NULC;

int getch(void)
{
	if (NULC == BUF)
		return getchar();
	int b = BUF;
	BUF = NULC;
	return b;
}

void ungetch(int c)
{
	if (NULC != BUF)
		printf("error: buffer already contains a character\n");
	else
		BUF = c;
}
