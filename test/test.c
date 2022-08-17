#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>


void sigint1(int k)
{
	write(1, "sigint1\n", 8);
}

void sigint2(int k)
{
	write(1, "sigint2\n", 8);
}

int main()
{
	signal(SIGINT, sigint1);
	signal(SIGINT, sigint2);

	while (1)
	{
		pause();
	}
}