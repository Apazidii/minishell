#include "minishell.h"



//int main(int agrc, char *argv[], char *envp[]) {
//	t_base	base;
//	int		error_code;
//
//	ft_bzero(&base, sizeof(base));
//
//	base.env_lst = parse_envp(envp);
////	if (errno != 0)
////		//обработка ошибок
////	ft_lstiter(env_lst, print_content);
//
//	while (1)
//	{
//		base.command = read_cmd(&base);
//		while (base.command == NULL)
//		{
//			printf("Malloc error\n");
//			base.command = read_cmd(&base);
//		}
//
//		if (is_space_string(base.command))
//		{
//
//			//УДАЛИТЬ
//			if (base.command[0] == '0')
//			{
//				free(base.command);
//				break;
//			}
//			//УДАЛИТЬ
//
//
//			error_code = lexer(base.command, &base);
//			if (error_code == SUCCES)
//				error_code = parser(base.lexer, &base);
//			if (error_code == SUCCES)
//				pre_action(&base);
//			if (error_code == MALLOC_ERROR)
//			{
//				printf("Malloc error\n");
//				ft_lstclear(&base.env_lst, free_dict);
//				ft_lstclear(&base.lexer, free_token);
//				ft_lstclear(&base.groups, free_group_list);
//				free(base.command);
//				return (1);
//			}
//
//		}
//	}
//	rl_clear_history();
//
//
//	ft_lstclear(&base.env_lst, free_dict);
//	free(base.command);
//
//	return 0;
//}



int main(int argc, char *argv[], char *envp[])
{
	char path[] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin";
	char *s = ft_strjoin(path, "/ls");
	char arr[1][2] = {"ls"};
	write(1, "11\n", 3);
	execve(s, argv, envp);
	perror(strerror(errno));
}