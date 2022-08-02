#include "minishell.h"

int is_space_string(char *s)
{
	while (*s != '\0')
	{
		if (*s != ' ')
			return (1);
		s++;
	}
	return (0);
}

char *add_newline(char *cmd)
{
	char *res;

	res = ft_strjoin(cmd, " newline");
	free(cmd);
	if (!res)
		return (NULL);
	return (res);
}

char *read_cmd(void)
{
	char *s;

	s = readline("minishell$ ");
	if (s && is_space_string(s))
		add_history(s);
	s = add_newline(s);
	return (s);
}

int get_cwd(t_base *base)
{
	getcwd(base->cwd, PATH_MAX);
	if (errno != 0)
	{
		perror(strerror(errno));
		return (1);
	}
	return (0);
}
