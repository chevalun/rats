#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

void *foo(void *);

int main()
{
	pthread_t ta, tb;
	pthread_create(&ta, NULL, foo, (void *) 0);
	pthread_create(&tb, NULL, foo, (void *) 1);
	pthread_join(ta, NULL);
	pthread_join(tb, NULL);
	return 0;
}

void *foo(void *arg)
{
	static int global_var = 42;
	int stack_var = 42;
	static int *heap_var;
	static __m128 r0;  // XMM register
	int temp[4], k;
	
	if(!arg) {
		heap_var = (int *) malloc(sizeof(int));
		*heap_var = 42;
		for(k = 0; k < 4; ++k)
			temp[k] = 42;
		r0 = _mm_load_ps((const float *) temp);
		long rst;
		__asm__(
			"movq $42, %%rax\n\t"
			"movq $3000000000, %%rcx\n\t"
			"loop: addq $-1, %%rcx\n\t"
			"jnz loop\n\t"
			"movq %%rax, %0"
			:"=r"(rst)
			:
			:"%rax", "%rcx"
		);		
//		sleep(1);
		_mm_store_ps((float *) temp, r0);
		printf("rsgister_rax = %ld\nregister_xmm = %d\nglobal_var = %d\nstack_var = %d\nheap_var = %d\n", rst, (int) temp[0], global_var, stack_var, *heap_var);
	} else {
		global_var = 64;
		stack_var = 64;
		*heap_var = 64;
		for(k = 0; k < 4; ++k)
			temp[k] = 64;
		r0 = _mm_load_ps((const float *) temp);
		__asm__(
			"movq $64, %%rax"
			:
			:
			:"%rax"
		);
	}
}