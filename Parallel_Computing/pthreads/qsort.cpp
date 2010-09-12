/*
*	A simple and straight-forward parallel implementation.
*/

#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <pthread.h>

#define MAXN 10000

using namespace std;

typedef struct {
	int *a;
	int lo, hi;
} quicksort_arg;

void* quicksort(void *arg);
pthread_t threadPool[MAXN];
int numThread;

int main()
{
	int a[MAXN], b[MAXN];
	
	for(int i = 0; i < MAXN; ++i)
		a[i] = rand();
	copy(a, a + MAXN, b);
	
	sort(a, a + MAXN);
	
	quicksort((void *) &(quicksort_arg){b, 0, MAXN - 1});
	for(int i = 0; i < numThread; ++i)
		pthread_join(threadPool[i], NULL);

	for(int i = 0; i < MAXN; ++i)
		assert(a[i] == b[i]);

	return 0;
}

void* quicksort(void *arg)
{
	quicksort_arg *x = (quicksort_arg*) arg;
	int *a = x->a;
	int i = x->lo, j = x->hi, key = a[(i + j) >> 1];
//	printf("%d %d\n", i, j);
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
	quicksort_arg *aa = (quicksort_arg*) malloc(sizeof(quicksort_arg)), *ab = (quicksort_arg*) malloc(sizeof(quicksort_arg));
	*aa = (quicksort_arg){a, i, x->hi}, *ab = (quicksort_arg){a, x->lo, j};
	if(i < x->hi) {
		pthread_create(&ta, NULL, quicksort, (void *) aa);
		threadPool[numThread++] = ta;
	}
	if(j > x->lo) {
		pthread_create(&tb, NULL, quicksort, (void *) ab);
		threadPool[numThread++] = tb;
	}
}