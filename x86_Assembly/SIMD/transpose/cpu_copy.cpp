#include <cstdlib>
#include "time_test.h"

#define DEM 2048

int main()
{
	int (*old_m)[DEM] = (int (*)[DEM]) malloc(DEM * DEM * sizeof(int));
	int (*new_m)[DEM] = (int (*)[DEM]) malloc(DEM * DEM * sizeof(int));

	for(int i = 0; i < DEM; ++i)
		for(int j = 0; j < DEM; ++j)
			old_m[i][j] = rand();
	
	START_TEST(10)
	for(int i = 0; i < DEM; ++i)
		for(int j = 0; j < DEM; ++j)
			new_m[i][j] = old_m[j][i];
	END_TEST
		
	free(old_m);
	free(new_m);
	return 0;
}
