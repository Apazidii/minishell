# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>


void print()
{
	write(1, "Hello wolrd\n", 12);
}

int main()
{
	int fd;

	fd = open("output.txt", O_WRONLY);
	if (fd == -1)
		printf("open error\n");
	else
	{
		fd = dup2(fd, 1);
		if (fd == -1)
			printf("dup2 error\n");
		else
		{
			printf("%d\n", fd);
			print();
		}
	}
}