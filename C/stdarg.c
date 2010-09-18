#include <stdarg.h>
#include <stdio.h>

void printargs(int arg, ...)
{
	va_list ap;
	int i;
	
	va_start(ap, arg);
	for(i = arg; i != -1; i = va_arg(ap, int))
		printf("%d\n", i);
	va_end(ap);	
}

int main()
{
	printargs(1, 2, 3, -1);
	return 0;
}