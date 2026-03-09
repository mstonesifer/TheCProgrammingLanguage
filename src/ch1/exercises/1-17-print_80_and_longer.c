#include <stdio.h>

#define THRESHOLD 80	/* Print all lines longer than threshold */

int get_line(char s[], int max);

/* prints all lines of an input greater than THRESHOLD */
int main()
{
	int i, c;
	int len;
	char buffer[THRESHOLD];

	while ((len = get_line(buffer, THRESHOLD)) > 0) {
		if (len >= THRESHOLD - 1) {
			printf("%s", buffer);
			while ((c = getchar()) != EOF && c != '\n') {
				putchar(c);
			}
			putchar('\n');
		}
	}

}

/* get_line: read a line into s, return length */
int get_line(char s[], int max)
{
	int i, c;

	// copy input to buffer until THRESHOLD met
	for (i = 0; i < max - 1 &&
	     (c = getchar()) != EOF &&
	     c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
