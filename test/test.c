#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#define _GNU_SOURCE 1
#include <string.h>
int main()
{
	int fd;
	char str[100];
	char putstr[] = "string";

	fd = open("ss",  O_CREAT | O_WRONLY | O_TRUNC, 0644);
	perror("open");


	write(fd, putstr, strlen(putstr));
	perror("write");

	int ret = read(fd, str, 100);
	perror("read");

	str[ret] = '\0';
	printf("%d _%s_\n",ret,  str);

}