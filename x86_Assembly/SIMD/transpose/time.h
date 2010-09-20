#include <ctime>
#include <cstdio>

#define START_TEST clock_t end, st = clock();
#define END_TEST end = clock(); printf("%.3lfs\n", ((double)end-st)/CLOCKS_PER_SEC);
