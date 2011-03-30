#include <cstdio>
#include <cstdlib>
#include <cuda.h>
#include "time_test.h"

#define DIM 2048
#define TILE_DIM 16
#define BLOCK_ROWS 16

__global__ void transpose(int *new_m, int *old_m, int dim)
{
	int xIndex = blockIdx.x * TILE_DIM + threadIdx.x;
	int yIndex = blockIdx.y * TILE_DIM + threadIdx.y;

	int index_in  = xIndex + dim * yIndex;
	int index_out = yIndex + dim * xIndex;

	for(int i = 0; i < TILE_DIM; i += BLOCK_ROWS)
		new_m[index_out + i] = old_m[index_in + i * dim];
}

int main()
{
	const int memSize = DIM * DIM * sizeof(int);
	int (*old_m)[DIM] = (int (*)[DIM]) malloc(memSize);
	int (*new_m)[DIM] = (int (*)[DIM]) malloc(memSize);
	
	for(int i = 0; i < DIM; ++i)
		for(int j = 0; j < DIM; ++j)
			old_m[i][j] = rand();
	
	START_TEST(10)
	
	dim3 grid(DIM/TILE_DIM, DIM/TILE_DIM), threads(TILE_DIM, BLOCK_ROWS);
	int *old_m_d, *new_m_d;
	cudaMalloc((void **) &old_m_d, memSize);
	cudaMalloc((void **) &new_m_d, memSize);
	cudaMemcpy(old_m_d, &(old_m[0][0]), memSize, cudaMemcpyHostToDevice);
	transpose<<<grid, threads>>>(new_m_d, old_m_d, DIM);
	cudaMemcpy(new_m, new_m_d, memSize, cudaMemcpyDeviceToHost);

	END_TEST
	
	return 0;
}
