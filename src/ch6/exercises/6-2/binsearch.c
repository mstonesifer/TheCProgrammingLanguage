#include <stdio.h>
#include "varnames.h"

/* binsearch:  find word in v[0]...v[n-1] */
char *strbsearch(char *w, char **v, int n)
{
	int r, mid;
	int low = 0;
	int high = n-1;

	while (low <= high) {
		mid = (low + high) / 2;
		if ((r = strcomp(w, v[mid])) < 0)
			high = mid - 1;
		else if (r > 0)
			low = mid + 1;
		else
			return v[mid];
	}
	return NULL;
}
