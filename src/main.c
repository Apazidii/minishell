#include "minishell.h"

static void	start_command(t_base *base)
{
	int	error_code;

	error_code = SUCCES;
	if (is_space_string(base->command))
	{
		base->command = add_newline(base->command);
		if (base->command == NULL)
		{
			perror("readline");
			error_code = MALLOC_ERROR;
		}
		if (error_code == SUCCES)
			error_code = lexer(base->command, base);
		if (error_code == SUCCES)
			error_code = parser(base->lexer, base);
		if (error_code == SUCCES)
			error_code = pre_action(base);
		base->exit_status = error_code;
		ft_lstclear(&base->lexer, free_token);
		ft_lstclear(&base->groups, free_group_list);
		errno = 0;
	}
}

static int	run_command(t_base *base)
{
	int		eof;

	set_interactive_mode_signals();
	base->command = read_cmd(base, &eof);
	while (base->command == NULL)
	{
		if (eof == 1)
			break ;
		perror("readline");
		base->command = read_cmd(base, &eof);
	}
	if (eof == 1)
		return (STOP);
	start_command(base);
	free(base->command);
	return (SUCCES);
}

int	main(int agrc, char *argv[], char *envp[])
{
	t_base	base;
	int		error_code;

	ft_bzero(&base, sizeof(base));
	base.env_arr = envp;
	base.env_lst = parse_envp(envp);
	while (1)
	{
		error_code = run_command(&base);
		if (error_code == STOP)
			break ;
	}
	rl_clear_history();
	ft_lstclear(&base.env_lst, free_dict);
	return (0);
}

