/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:35:30 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void proc_exit(t_base *base, int k)
{
	ft_lstclear(&base->lexer, free_token);
	ft_lstclear(&base->groups, free_group_list);
	free(base->command);
	rl_clear_history();
	ft_lstclear(&base->env_lst, free_dict);
	exit(k);
}

int str_isdigit(char *s)
{
	while (*s != '\0')
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	builtint_exit(t_base *base, char **arg, int num_arg)
{
	if (num_arg == 1)
		proc_exit(base, 0);
	if (str_isdigit(arg[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		proc_exit(base, 2);
	}
	if (num_arg > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		proc_exit(base, 1);
	}
	proc_exit(base, ft_atoi(arg[1]));
	return (SUCCES);
}
