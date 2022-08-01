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

int main(int agrc, char *argv[], char *envp[]) {
	t_base	base;
	int		error_code;

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
			if (error_code == 1)
			{
				ft_lstclear(&base.env_lst, free_dict);
				ft_lstclear(&base.lexer, free_token);
				free(base.command);
				return (1);
			}
			if (error_code == 0)
			{
				parser(base.lexer, &base);
			}
		}
	}
	rl_clear_history();


	ft_lstclear(&base.env_lst, free_dict);
	return 0;
}



//int main()
//{
//	char **arr;
//
//	char *s1 = malloc(2);
//	s1[0] = '1';
//	s1[1] = '\0';
//	char *s2 = malloc(2);
//	s2[0] = '2';
//	s2[1] = '\0';
//	char *s3 = malloc(2);
//	s3[0] = '3';
//	s3[1] = '\0';
//	char *s4 = malloc(2);
//	s4[0] = '4';
//	s4[1] = '\0';
//
//	arr = (char **) malloc(sizeof(char *) * 3);
//	arr[0] = s1;
//	arr[1] = s2;
//	arr[2] = NULL;
//
//	arr = arr_add_str(arr, s3, 1);
//	arr = arr_add_str(arr, s4, 1);
//	int i = 0;
//	while ((arr)[i])
//	{
//		printf("_%s_", (arr)[i]);
//		i++;
//	}
//}