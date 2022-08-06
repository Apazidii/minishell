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



char *get_promt(t_base *base)
{
	char *res;

	if (get_cwd(base))
		return (NULL);
	res = ft_strjoin("\033[0;32mminishell\033[0m:\033[0;34m", base->cwd);
	if (res == NULL)
		return (NULL);
	res = ft_strjoin(res, "\033[0m$ ");
	if (res == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char *read_cmd(t_base *base)
{
	char *s;
	char *promt;

	promt = get_promt(base);
	if (promt == NULL)
	{
		printf("Malloc error\n");
		return (NULL);
	}
	s = readline(promt);
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

