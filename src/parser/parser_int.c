#include "minishell.h"
#include "parser.h"

int len_arr_int(int *arr)
{
	int i;

	i = 0;
	while (arr[i] != -1)
		i++;
	return (i);
}

int *add_arr_int(int *arr, int rep_var)
{
	int l;
	int *res;
	int i;

	if (arr == NULL)
	{
		res = (int *) ft_calloc(sizeof(int), 2);
		if (!res)
			return (NULL);
		res[0] = rep_var;
		res[1] = -1;
		return (res);
	}
	l = len_arr_int(arr);
	res = (int *) ft_calloc(sizeof(int), l + 2);
	if (!res)
	{
		free(arr);
		return (NULL);
	}
	i = 0;
	while (arr[i] != -1)
	{
		res[i] = arr[i];
		i++;
	}
	res[i] = rep_var;
	res[i + 1] = -1;
	free(arr);
	return (res);
}