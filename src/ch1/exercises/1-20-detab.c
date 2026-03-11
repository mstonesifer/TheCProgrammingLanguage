#include <stdio.h>

#define TABSIZE 8	/* The number of spaces before tabstop */

int get_text(char chunk[], int size);

/* replaces tabs in an input with the proper number of spaces to the next
 * tab stop */
int main()
{
	int len;			/* current chunk length */
	char chunk[TABSIZE + 1];	/* current input chunk */

	/* while there is text */
	while ((len = get_text(chunk, TABSIZE) > 0))
		/* print current contents */
		printf("%s", chunk);
	return 0;
}

/* get_text: read text into s, return length */
int get_text(char s[], int size)
{
	int c, i;
	for (i = 0; i < size
	    && (c = getchar()) != EOF
	    && c != '\n'
	    && c != '\t'; ++i) {
		s[i] = c;
	}

	/* if tab, replace tab and remaining cols with spaces */
	if (c == '\t') {
		while (i < size) {
			s[i] = ' ';
			++i;
		}
	/* if new line, print immediately */
	} else if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

