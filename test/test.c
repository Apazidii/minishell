#include <stdlib.h>
#include <stdio.h>

int len_arr_str(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
		i++;
	return (i);
}

int main()
{
	char s1[] = "11";
	char s2[] = "22";
	char s3[] = "33";
	char s4[] = "44";

	char **r;

	*r = NULL;

	char *s[] = {s1, s2, s3, s4, NULL};
	printf("%d\n", len_arr_str(s));


}