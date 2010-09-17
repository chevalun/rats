#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void fp_exception(int sig)
{
	printf("Float-point Exception!\n");
	exit(-1);
}

int main()
{
	signal(SIGFPE, fp_exception);
	int a = 42/0;
	return 0;
}