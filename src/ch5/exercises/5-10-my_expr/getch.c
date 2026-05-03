#include <stdio.h>

#define BUFSIZE	100

static int buf;		/* single char buffer */

/* get a (possibly pushed back) character */
int getch(void)
{
	if (buf == '\0')		/* buffer empty */
		return getchar();

	int t = buf;
	buf = '\0';
	return t;
}

void ungetch(int c) /* push character back on input */
{
	if (buf != '\0')
		printf("ungetch: buffer already has value\n");
	else
		buf = c;
}
