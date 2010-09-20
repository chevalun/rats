#include <stdio.h>

int main()
{
	long rst;
	__asm__(
		"pushfq\n\t"
		"popq %%rax\n\t"
		"movq %%rax, %0"
		:"=r"(rst)
		:
		:"%rax"
	);
	
	printf("%lx\n", rst);
	return 0;
}