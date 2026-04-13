#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define HEX_MULTIPLIER 16	/* represents each place value of a hex column */

/* prototypes */
int htoi(char s[]);

/* converts hex string to integer equivalent */
int main(void)
{
	char hex[] = "0x2CF";

	int val = htoi(hex);

	printf("0x1F (hex) = %i (dec)\n", val);

	return 0;
}

int htoi(char s[])
{
	int n = 0;
	int c;

	for (int i = 0; s[i] != '\0'; ++i) {
		if ((i == 0 || i == 1) && (s[i] == '0' || s[i] == 'x' || s[i] == 'X'))
			continue;

		if (isdigit(s[i]))
			n = n * HEX_MULTIPLIER + (s[i] - '0');
		else if ((c = tolower(s[i])) >= 'a' && c <= 'f')
			n = n * HEX_MULTIPLIER + (c - 'a' + 10);
		
	}
	return n;
}
