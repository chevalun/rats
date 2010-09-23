#ifndef __TIME_TEST_CHEVALUN
#define __TIME_TEST_CHEVALUN

#include <ctime>
#include <cstdio>

#define START_TEST(re) int REPEAT = re; while(REPEAT--){ clock_t end, st = clock();
#define END_TEST end = clock(); printf("%.3lfs\n", ((double)end-st)/CLOCKS_PER_SEC);}

#endif