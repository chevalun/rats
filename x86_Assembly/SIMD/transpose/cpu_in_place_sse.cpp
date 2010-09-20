#include <cstdlib>
#include <xmmintrin.h>
#include "time.h"

#define DEM 2048

int main()
{
	int (*mat)[DEM] = (int (*)[DEM]) malloc(DEM * DEM * sizeof(int));

	for(int i = 0; i < DEM; ++i)
		for(int j = 0; j < DEM; ++j)
			mat[i][j] = rand();

	START_TEST

	__m128 r0, r1;
	for(int i = 0; i < DEM; ++i)
		for(int j = 0; j < DEM; j += 4) {
			int temp[4];
			for(int k = 0; k < 4; ++k)
				temp[k] = mat[j+k][i];
			r0 = _mm_load_ps((const float *) temp);
			r1 = _mm_load_ps((const float *) &mat[i][j]);
			_mm_store_ps((float *) &mat[i][j], r0);
			_mm_store_ps((float *) temp, r0);
			for(int k = 0; k < 4; ++k)
				mat[j+k][i] = temp[k];			
		}

	END_TEST
		
	free(mat);
	return 0;
}
