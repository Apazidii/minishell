#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int main()
{
	int k =	execve("qwe", NULL, 0);
	printf("%d\n",errno);
	perror("my");
}