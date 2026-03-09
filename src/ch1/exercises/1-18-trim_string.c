#include <stdio.h>

#define MAXLINE 1000	/* maximum input line size */

int get_trimmed_line(char s[], int lim);
void println(char s[]);

/* prints input lines without trailing whitespace (blanks and tabs) and no empty lines */

int main()
{
	int len;		/* current line length */
	char line[MAXLINE];	/* current input line */

	/* while there is a line of text */
	while ((len = get_trimmed_line(line, MAXLINE)) > 0) {
		if(line[0] != '\n')	/* only print non-blank lines */
			printf("%s", line);
	}
	return 0;
}

/* get_trimmed_line: read a line into s and remove all trailing spaces or tabs */
int get_trimmed_line(char s[], int lim)
{
	int c, i, j;

	for (i = 0; i < lim-1 &&
	     (c = getchar()) != EOF &&
	     c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		for (j = i-1; j >= 0 && (s[j] == ' ' || s[j] == '\t'); --j);
		++j;
		s[j] = c;
		++j;
		s[j] = '\0';
		return j;
	}
	s[i] = '\0';
	return i;
}

/* println: prints the contents of s with tab and empty space visualization
 * assumes s contains null char to end the string */
void println (char s[])
{
	int i = 0;
	while(s[i] != '\n' && s[i] != '\0') {
		if (s[i] == '\t') {
			putchar('\\');
			putchar('t');
		} else if (s[i] == ' ') {
			putchar('\\');
			putchar('s');
		} else if (s[i] == '\b') {
			putchar('\\');
			putchar('b');
		} else if (s[i] == '\\') {
			putchar('\\');
			putchar('\\');
		} else {
			putchar(s[i]);
		}
		++i;
	}
	putchar('\n');
}
