#include <stdio.h>

#define FALSE 0
#define TRUE 1

int any(char s1[], char s2[]);

/* return the first location in s1 where a char from s2 occurs */
int main(void)
{
	char foo[] = "the quick brown fox jumped over the lazy dog";
	char find[] = "foo";

	printf("Expected: 12\n");
	printf("Actual:   %d\n", any(foo, find));
	
}

int any(char s1[], char s2[])
{

	for (int i = 0; s1[i] != '\0'; ++i) {
		for (int j = 0; s2[j] != '\0'; ++j) {
			if (s1[i] == s2[j]) {
				return i;
			}
		}
	}
}
