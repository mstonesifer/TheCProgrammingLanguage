#include <stdio.h>
#include <stdlib.h>

#include "varnames.h"
#include "keywords.c"

/* K&R exercise 6-2 */
/* Write a program that reads a C program and prints in		*/
/* alphabetical order each group of variable names that		*/
/* are identical in the first 6 characters, but different	*/
/* somehwere thereafter. Don't count words within strings	*/
/* and comments. Make a 6 parameter that can be set from	*/
/* the command line.						*/
int main(int argc, char *argv[])
{
	int i;
	char *word;
	char *vars[MAXWORDS];

	/* not overdoing reading params here -> not the point of this exercise */
	int mc = (argc > 1 && HYPC == **++argv) ? my_atoi(*argv) : DEF_MC;

	char b[MAXWORDLEN];

	getword(b, MAXWORDLEN);
	char *t = strbsearch(b, varkeys, NVKEYS);
	printf("%sfound\n", (NULL == t) ? "not " : "");

	/* get var names */
//	getvarnames(vars, MAXWORDS);

	/* compare first <mc> chars of var names, save to tree if same */
//	for (i = MAXWORDS - 1; i > 0 && NULL != (word = *vars++); i--) {
//		if (nstrcmp(*vars, mc))
//			tadd(*vars);
//
//	}	

	/* print tree */

	return 0;
}

/* getvarnames:  gets all variable names from an input */
//void get_words(char **words, int limit)
//{
//	int i;
//	char *word;
//
//	/* only need to store words following keywords */
//	for (i = 0; i < limit && EOF != getword(word))
//
//}
