#include <cstdlib>
#include <xmmintrin.h>
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

	__m128 r0;
	for(int i = 0; i < DEM; ++i)
		for(int j = 0; j < DEM; j += 4) {
			int temp[4];
			for(int k = 0; k < 4; ++k)
				temp[k] = old_m[j+k][i];
			r0 = _mm_load_ps((const float *)temp);
			_mm_store_ps((float *)&new_m[i][j], r0);
		}
	END_TEST
		
	free(old_m);
	free(new_m);
	return 0;
}
