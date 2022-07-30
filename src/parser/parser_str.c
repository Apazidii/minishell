#include "minishell.h"
#include "parser.h"


static int len_arr_str(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
		i++;
	return (i);
}

void free_arr_str(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


char **arr_add_str(char **arr, char *str, int len_str)
{
	int		l;
	char	**res;
	int 	i;

	l = len_arr_str(arr);
	res = (char **)ft_calloc(sizeof(char *), l + 2);
	if (!res)
	{
		free_arr_str(arr);
		return (NULL);
	}
	i = 0;
	while (arr[i])
	{
		res[i] = arr[i];
		i++;
	}
	res[i] = ft_substr(str, 0, len_str);
	if (!res[i])
	{
		free_arr_str(res);
		free_arr_str(arr);
		return (NULL);
	}
	res[i + 1] = NULL;
	free(arr);
	return (res);
}
