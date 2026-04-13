#include <stdio.h>

#define FALSE 0
#define TRUE 1

void squeeze(char s1[], char s2[]);

/* remove all characters from s1 that match any character in s2 */
int main(void)
{
	char foo[] = "the quick brown fox jumped over the lazy dog";
	char remove[] = "apple";

	squeeze(foo, remove);

	printf("Expected: th quick brown fox jumd ovr th zy dog\n");
	printf("Actual:   ");
	puts(foo);
}

void squeeze(char s1[], char s2[])
{
	int i, j, k, x;

	x = FALSE;
	for (i = k = 0; s1[i] != '\0'; ++i) {
		for (j = 0; x == FALSE && s2[j] != '\0'; ++j) {
			if (s1[i] == s2[j]) {
				x = TRUE;
			}
		}
		if(x != TRUE)
			s1[k++] = s1[i];
		x = FALSE;
	}
	s1[k] = '\0';
}
