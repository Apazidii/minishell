# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>




int main()
{
	char s[] = "123456789";

	printf("%.*s\n", 5, s);
}