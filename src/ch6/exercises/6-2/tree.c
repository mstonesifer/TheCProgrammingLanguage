#include <stdio.h>
#include <stdlib.h>

#include "varnames.h"

/* tree node */
struct tnode {
	char *value;		/* stored word  */
	struct tnode *lb;	/* left branch  */
	struct tnode *rb;	/* right branch */
};

static struct tnode *talloc(void);

/* addtree:  add a node with w, at or below p*/
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {		/* a new word has arrived */
		p = talloc();		/* make a new node */
		p->value = strdupe(w);
		p->lb = p->rb = NULL;
	} else if ((cond = strcomp(w, p->value)) == 0)
		;			/* if exists; do nothing */
	else if (cond < 0)		/* less than into left subtree */
		p->lb = addtree(p->lb, w);
	else				/* greater than into right subtree */
		p->rb = addtree(p->rb, w);
	return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->lb);
		printf("%s\n", p->value);
		treeprint(p->rb);
	}
}

/* talloc:  make a tnode */
static struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}
