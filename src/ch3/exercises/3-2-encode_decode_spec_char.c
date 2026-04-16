#include <stdio.h>

/* k&r exercise 3-2 */

/*
 * Write a function `escape(s,t)` that converts characters like
 * newline and tab into visible escape sequences like \n and \t
 * as it copies the string t to s. Use a `switch`. Write a function
 * for the other direction as well, convert escape sequences into
 * real characters.
 */

/* macros */
#define ARR_SZ 5000		/* array size */

/* prototypes */
void encode_escapes(char [], char []);
void decode_escapes(char [], char []);

int main()
{
	int c, i;
	char s[ARR_SZ];
	char t[ARR_SZ];

	for (i=0; i<ARR_SZ-1 && (c=getchar()) != EOF; ++i)
		s[i] = c;
	s[++i] = '\0';

	printf("Original input:\n%s\n", s);

	encode_escapes(s, t);

	printf("Encoded input:\n%s\n", t);
	for (i=0; i<ARR_SZ; ++i)
		s[i] = 0;
	s[ARR_SZ - 1] = '\0';

	decode_escapes(s, t);

	printf("Decoded input:\n%s\n", s);

	return 0;
}

/* encode_escapes: convets characters in s to escape strings
 * as the string is copied into t; assumes t is large enough */
void encode_escapes(char s[], char t[])
{
	int i, j;
	for (i = j = 0; s[i] != '\0'; ++i) {
		switch (s[i]) {
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			case '\b':
				t[j++] = '\\';
				t[j++] = 'b';
				break;
			case '\\':
				t[j++] = '\\';
				t[j++] = '\\';
				break;
			default:
				t[j++] = s[i];
				break;
		}
	}
}

/* decode_escapes: converts escape strings in t to encoded
 * characters as the string is copied into s; assumes s
 * is large enough */
void decode_escapes(char s[], char t[])
{
	int i, j;
	for (i = j = 0; t[i] != '\0'; ++i) {
		switch (t[i]) {
			case '\\':
				switch(t[i+1]) {
					case 'n':
						s[j] = '\n';
						i++;
						break;
					case 't':
						s[j] = '\t';
						i++;
						break;
					case 'b':
						s[j] = '\b';
						i++;
						break;
					case '\\':
						s[j] = '\\';
						i++;
						break;
				}
				break;
			default:
				s[j] = t[i];
				break;
		}
		j++;
	}
}
