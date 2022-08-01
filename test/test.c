#include <stdlib.h>
#include <stdio.h>

char * ss(char *s)
{
	s = (char *)malloc(sizeof(char) * 1);
	s = "qw";
	return (s);
}

int main()
{
	char *s;
	s = ss(s);
	printf("%s\n", s);
	free(s);
}