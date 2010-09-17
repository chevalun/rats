#include <stdio.h>

#define BUFF_SIZE 2048

int main()
{
	static char buf[BUFF_SIZE];  // Notice the 'static' here.
	int i;
	
	setbuffer(stdout, buf, BUFF_SIZE);
	for(i = 0; i < 2047; ++i)
		putchar('*');
	sleep(1);
	putchar('\n');
	
	setbuffer(stdout, malloc(BUFF_SIZE * sizeof(char)), BUFF_SIZE);
	for(i = 0; i < 2047; ++i)
		putchar('*');
	sleep(1);
	putchar('\n');
	return 0;
}