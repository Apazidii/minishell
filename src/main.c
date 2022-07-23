#include "minishell.h"


int main(int agrc, char *argv[], char *envp[]) {
	t_list *env_lst;
	env_lst = parse_envp(envp);
	if (env_lst)
		(void) //обработка ошибок
	ft_lstiter(env_lst, print_content);
	free_lst(env_lst);
	return 0;
}

