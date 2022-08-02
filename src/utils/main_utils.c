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
	base->cwd.size = 100;
	base->cwd.path = ft_calloc(sizeof(char), base->cwd.size);
	if (base->cwd.path == NULL)
		return (MALLOC_ERROR);
	base->cwd.path = getcwd(base->cwd.path, base->cwd.size);

	return (SUCCES);
}

int add_size_cwd(t_base *base)
{
	if (base->cwd.path != NULL)
		free(base->cwd.path);
	base->cwd.size += 100;
	base->cwd.path = ft_calloc(sizeof(char), base->cwd.size);
	if (base->cwd.path == NULL)
		return (MALLOC_ERROR);
	return (SUCCES);
}