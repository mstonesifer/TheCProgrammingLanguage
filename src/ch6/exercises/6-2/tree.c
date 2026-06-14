#include <stdio.h>

/* tree node */
struct tnode {
	char *value;		/* stored word  */
	struct tnode *lb;	/* left branch  */
	struct tnode *rb;	/* right branch */
};

