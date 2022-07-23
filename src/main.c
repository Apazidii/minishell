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

char *read_cmd(void)
{
    char *s;

    s = readline("minishell$ ");
    if (s && is_space_string(s))
		add_history(s);
	return (s);
}

int main(int agrc, char *argv[], char *envp[]) {
	t_base base;

	base.env_lst = parse_envp(envp);
//	if (errno != 0)
//		//обработка ошибок
//	ft_lstiter(env_lst, print_content);
	while (1)
	{
		base.command = read_cmd();
		free(base.command);
	}





	free_lst(base.env_lst);
	return 0;
}

