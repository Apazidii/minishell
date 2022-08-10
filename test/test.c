#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main()
{
	int buf = dup(0);

	int fd;

	dup2(0, 1);
	write(0, "123", 3);

}