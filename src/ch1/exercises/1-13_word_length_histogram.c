#include <stdio.h>

/* create a word length histogram from an input */

void main()
{
	// need to resolve what makes the end of a word
	
	int c, i, nchar;
	int wordLen[10];

	for (i = 0; i < 10; ++i)
		nchar[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c != ' ' && c != '\n' && c != '\t') {
			

