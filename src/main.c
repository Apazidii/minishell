#include "minishell.h"



int main(int agrc, char *argv[], char *envp[]) {
	t_base	base;
	int		error_code;

	ft_bzero(&base, sizeof(base));

	base.env_lst = parse_envp(envp);
//	if (errno != 0)
//		//обработка ошибок
//	ft_lstiter(env_lst, print_content);

	while (1)
	{
		base.command = read_cmd();
		while (base.command == NULL)
		{
			printf("Malloc error\n");
			base.command = read_cmd();
		}

		if (is_space_string(base.command))
		{

			//УДАЛИТЬ
			if (base.command[0] == '0')
			{
				free(base.command);
				break;
			}
			//УДАЛИТЬ


			error_code = lexer(base.command, &base);
			if (error_code == 0)
				error_code = parser(base.lexer, &base);
			if (error_code == 0)
			{

			}
			if (error_code == 1)
			{
				ft_lstclear(&base.env_lst, free_dict);
				ft_lstclear(&base.lexer, free_token);
				ft_lstclear(&base.groups, free_group_list);
				free(base.command);
				printf("Malloc error\n");
				return (1);
			}
		}
	}
	rl_clear_history();


	ft_lstclear(&base.env_lst, free_dict);
	free(base.command);

	return 0;
}



//int main()
//{
//	t_base	base;
//
//	pwd(&base);
//}