#include "minishell.h"

int cd(char **arg, int num_arg)
{
	if (num_arg != 2)
		printf("minishell: cd: too many arguments");
	if (chdir(arg[1]) == -1)
	{
		perror(strerror(errno));
		errno = 0;
		return (-1);
	}
	return (1);
}