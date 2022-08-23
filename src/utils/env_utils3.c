#include "../../hdr/minishell.h"

void	copy_from_dest(char *dest, char **res, size_t *i)
{
	*i = 0;
	while (dest[*i] != '\0')
	{
		(*res)[*i] = dest[*i];
		(*i)++;
	}
}
