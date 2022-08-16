#include "minishell.h"



int main(int agrc, char *argv[], char *envp[]) {
	t_base	base;
	int		error_code;
	int		eof;

	ft_bzero(&base, sizeof(base));
	base.env_arr = envp;
	base.env_lst = parse_envp(envp);
//	if (errno != 0)
//		//обработка ошибок
//	ft_lstiter(env_lst, print_content);


	signal(SIGINT, sig_int);


	while (1)
	{
		error_code = SUCCES;
		base.command = read_cmd(&base, &eof);
		while (base.command == NULL)
		{
			if (eof == 1)
				break;
			perror("readline");
			base.command = read_cmd(&base, &eof);
		}
		if (eof == 1)
			break;
		if (is_space_string(base.command))
		{
			error_code = SUCCES;
			base.command = add_newline(base.command);
			if (base.command == NULL)
			{
				perror("readline");
				error_code = MALLOC_ERROR;
			}

			if (error_code == SUCCES)
				error_code = lexer(base.command, &base);
			if (error_code == SUCCES)
				error_code = parser(base.lexer, &base);
			if (error_code == SUCCES)
				error_code = pre_action(&base);
//			printf("exit code = %d\n", error_code);
			ft_lstclear(&base.lexer, free_token);
			ft_lstclear(&base.groups, free_group_list);
			if (error_code == MALLOC_ERROR)
			{
				printf("Malloc error\n");
				errno = 0;
				break;
			}
			errno = 0;
		}
		free(base.command);
	}
	rl_clear_history();


	ft_lstclear(&base.env_lst, free_dict);

	return 0;
}
