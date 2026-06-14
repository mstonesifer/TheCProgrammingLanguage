#include <stdio.h>
#include "varnames.h"

static int BUF = NULC;

/* getch:  gets a character from the buffer or from input if buffer empty */
int getch(void)
{
	if (NULC == BUF)
		return getchar();
	int b = BUF;
	BUF = NULC;
	return b;
}

/* ungetch:  places a character onto the buffer */
void ungetch(int c)
{
	if (NULC != BUF)
		printf("error: buffer already contains a character\n");
	else
		BUF = c;
}
