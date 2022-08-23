#include "../../hdr/minishell.h"

int	free_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (1);
}

int	free_one(void *k)
{
	free(k);
	return (1);
}
