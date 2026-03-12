#include <stdio.h>

#define TABSIZE 8	/* The number of spaces before tabstop */

int detab_text(char buffer[], int size);

/* replaces tabs in an input with the proper number of spaces to the next
 * tab stop */
int main()
{
	int len;			/* current buffer length */
	char buffer[TABSIZE + 1];	/* current input chunk */

	/* while there is text */
	while ((len = detab_text(buffer, TABSIZE) > 0))
		/* print current contents */
		printf("%s", buffer);
	return 0;
}

/* detab_text: read text into s, return length */
int detab_text(char s[], int size)
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

