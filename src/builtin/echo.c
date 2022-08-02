#include "minishell.h"

void echo(char **arg, int num_arg)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (ft_strncmp(arg[i], "-n", 2) == 0)
	{
		newline = 0;
		i++;
	}
	while (i < num_arg)
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (i != num_arg - 1)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}