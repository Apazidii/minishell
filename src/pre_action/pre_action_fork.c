/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_action_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:36:28 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "pre_action.h"

int	run_command(t_group *group, t_base *base)
{
	int	error_code;

	close_unused_fd(group);
	error_code = chech_builtin(group, base);
	if (error_code == NOT_FOUND)
		error_code = run_exec(base, group->arg_str[0], group->arg_str);
	return (error_code);
}

int	apply_fork(t_group *group, t_base *base, int i)
{
	int	error_code;

	base->pid[i] = fork();
	if (base->pid[i] == -1)
	{
		ft_putendl_fd("Fork failed", 2);
		return (FORK_ERROR);
	}
	if (base->pid[i] == 0)
	{
		error_code = run_command(group, base);
		exit(error_code);
	}
	else
		return (SUCCES);
}
