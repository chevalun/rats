#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int value = 5;

int main()
{
	pid_t pid;
	pid = fork();
	if (!pid) {
		value += 15;
	} else if (pid > 0) {
		wait(NULL);
		printf("PARENT:value=%d\n", value);
		exit(0);
	}
	return 0;
}