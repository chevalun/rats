/*
*	A simple and straight-forward parallel implementation.
*/

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <pthread.h>

#define MAXN 1000

using namespace std;

typedef struct {
	int *a;
	int lo, hi;
} quicksort_arg;

void* quicksort(void *arg);

int main()
{
	int a[MAXN], b[MAXN];
	
	for(int i = 0; i < MAXN; ++i)
		a[i] = rand();
	copy(a, a + MAXN, b);
	
	sort(a, a + MAXN);
	quicksort((void *) &(quicksort_arg){b, 0, MAXN - 1});
	
	for(int i = 0; i < MAXN; ++i)
		assert(a[i] == b[i]);

	return 0;
}

void* quicksort(void *arg)
{
	quicksort_arg *x = (quicksort_arg*) arg;
	int *a = x->a;
	int i = x->lo, j = x->hi, key = a[(i + j) >> 1];
	do {
		while(a[i] < key)
			++i;
		while(a[j] > key)
			--j;
		if(i <= j) {
			swap(a[i], a[j]);
			++i;
			--j;
		}
	} while(i <= j);
	
	pthread_t ta, tb;
	quicksort_arg aa = (quicksort_arg){a, i, x->hi}, ab = (quicksort_arg){a, x->lo, j};
	if(i < x->hi)
		pthread_create(&ta, NULL, quicksort, (void *) &aa);
	if(j > x->lo)
		pthread_create(&tb, NULL, quicksort, (void *) &ab);
	if(i < x->hi)
		pthread_join(ta, NULL);
	if(j > x->lo)
		pthread_join(tb, NULL);			
}