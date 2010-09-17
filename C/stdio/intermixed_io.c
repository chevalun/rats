#include <stdio.h>

#define BUFF_SIZE 1024

int main()
{
	char buf[BUFF_SIZE];
	FILE *foo = fopen("test", "r+");
	int i;
	fread(buf, sizeof(char), 10, foo);
	for(i = 0; i < 10; ++i)
		++buf[i];
//	rewind(foo);	
	fwrite(buf, sizeof(char), 10, foo); // Seems that it is not necessary to put a fseek() between fwrite() and fread() on my Mac OS X.
	return 0;
}