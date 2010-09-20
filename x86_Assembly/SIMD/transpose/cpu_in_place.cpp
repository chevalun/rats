#include <algorithm>
#include <cstdlib>
#include "time.h"

#define DEM 2048

int main()
{
	int (*mat)[DEM] = (int (*)[DEM]) malloc(DEM * DEM * sizeof(int));
	
	for(int i = 0; i < DEM; ++i)
		for(int j = 0; j < DEM; ++j)
			mat[i][j] = rand();
	
	START_TEST
	for(int i = 0; i < DEM; ++i)
		for(int j = i + 1; j < DEM; ++j)
			std::swap(mat[i][j], mat[j][i]);
	END_TEST

	free(mat);
	return 0;
}
