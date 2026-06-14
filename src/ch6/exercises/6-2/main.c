#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "varnames.h"
#include "keywords.c"

struct tnode *get_var_names(char **, int, struct tnode *);
struct tnode *store_next(struct tnode *);

/* K&R exercise 6-2 */
/* Write a program that reads a C program and prints in		*/
/* alphabetical order each group of variable names that		*/
/* are identical in the first 6 characters, but different	*/
/* somehwere thereafter. Don't count words within strings	*/
/* and comments. Make a 6 parameter that can be set from	*/
/* the command line.						*/
int main(int argc, char *argv[])
{
	int _mycooltestvar = 0;
	int i;
	char *word;
	char *vars[MAXWORDS];
	struct tnode *root;

	/* not overdoing reading params here -> not the point of this exercise */
	int mc = (argc > 1 && HYPC == **++argv) ? my_atoi(*argv) : DEF_MC;

	/* get var names */
	root = NULL;
	root = get_var_names(vars, MAXWORDS, root);


	/* compare first <mc> chars of var names, save to tree if same */
//	for (i = MAXWORDS - 1; i > 0 && NULL != (word = *vars++); i--) {
//		if (nstrcmp(*vars, mc))
//			tadd(*vars);
//
//	}	

	printf("Printing all variable names...\n");
	/* print tree */
	treeprint(root);

	return 0;
}

/* get_var_names:  gets all variable names from an input */
struct tnode *get_var_names(char **words, int limit, struct tnode *t)
{
	int i;
	char word[MAXWORDLEN];

	/* only need to store words following keywords */
	for (i = 0; i < limit && EOF != getword(word, MAXWORDLEN); i++)
		/* if word is found, next word might be varname */
		if (NULL != strbsearch(word, varkeys, NVKEYS))
			t = store_next(t);
	return t;
}

/* store_next:  stores next word from input onto tree */
struct tnode *store_next(struct tnode *t)
{
	char word[MAXWORDLEN];		/* word to possibly store */
	char la[2];			/* look ahead character */
	/* todo: figure out a way to bubble up eof */
	/* side note: maybe this is bad design because we
	 * have nested get words; try to think of a better way */
	if (EOF != getword(word, MAXWORDLEN) &&		/* don't store EOF */
	    (isalpha(word[0]) || UNSC == word[0]) &&	/* first char must be letter or '_' */
	    OPC != getword(la, 2))			/* if next is open paren, it's a function */
		t = addtree(t, word);
	return t;
}	
