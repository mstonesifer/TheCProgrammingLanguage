#include <stdio.h>

#define TABSIZE 8	/* The number of spaces before tabstop */

/* replaces space in an input with the proper number of tabs to the next
 * tab stop */
int main()
{
	int c, i;
	char arr[TABSIZE + 1];		/* space char buffer */

	i = 0;
	/* while there is text */
	while ((c = getchar()) != EOF) {
		/* if arr is full */
		if (i == TABSIZE-1) {
			putchar('\t');		/* put a tab */
			i = 0;			/* reset index */
		/* otherwise, if current char is space */
		} else if (c == ' ') {
			arr[i] = c;		/* put in array */
			++i;			/* incr to next index */
		/* otherwise, if tab and spaces exist, replace spaces */
		} else if (c == '\t' && i != 0) {
			putchar(c);
			i = 0;
		/* otherwise, if current char is tab or nl or spaces in buffer */
		} else if (c == '\n' || i != 0) {
			arr[i] = c;		/* put in array */
			arr[i+1] = '\0';	/* term array */
			printf("%s", arr);	/* print array */
			i = 0;			/* reset index */
		/* otherwise */
		} else {
			putchar(c);	/* put the char */
			i = 0;		/* reset index */
		}
	}
	putchar('\n');
	return 0;
}
