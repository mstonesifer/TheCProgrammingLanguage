#include <stdio.h>

/* k&r page 58 example binsearch */

/* macros */
#define ARR_SZ 5	/* size of array */

/* prototypes */
int binsearch(int, int [], int n);

int main(void)
{
	int vector[ARR_SZ] = {3, 5, 7, 12, 18};
	int search = 2;
	
	int r = binsearch(search, vector, ARR_SZ);
	printf("Value %i %s %i.\n",
		search,
		(r == -1) ? "not found" : "found at position",
		r);
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
 * returns the position of the value if found; -1 when no match */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else	/* found match */
			return mid;
	}
	return -1;	/* no match */
}
