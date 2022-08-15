#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>


int main()
{

	char c;

	scanf("%c", &c);
	printf("char = %d", c);
}