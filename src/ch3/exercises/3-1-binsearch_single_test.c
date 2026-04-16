#include <stdio.h>

/* k&r exercise 3-1 */

/*
 * Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write
 * a version with only one test inside the loop and measure
 * the difference in runtime.
 */

/* macros */
#define ARR_SZ 14		/* size of array */
#define ITERATIONS 1	/* run search x num times to measure perf */

/* prototypes */
int binsearch(int, int [], int);
int binsearch_st(int, int [], int);

int main(void)
{
	int vector[ARR_SZ] = {3, 5, 7, 12, 18, 30, 41, 99, 138, 226, 934, 1024, 1192, 2048};
	int search;

	int r;	
	for (int i = 0; i < ARR_SZ; ++i) {
		search = vector[i];
		//r = binsearch(search, vector, ARR_SZ);
		r = binsearch_st(search, vector, ARR_SZ);

		printf("Value %i %s %i.\n",
			search,
			(r == -1) ? "not found" : "found at position",
			r);
	}
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

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
 * returns the position of the value if found; -1 when no match
 * remarks: uses only one test inside the loop */
int binsearch_st(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = low + (high-low) / 2;
		//printf("low: %i, mid: %i, high: %i\n", low, mid, high);
		if (x <= v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return (low < n && x == v[low]) ? low : -1;
}
