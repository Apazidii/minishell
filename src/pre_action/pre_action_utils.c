/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_action_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:36:57 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "pre_action.h"

int	kill_pid(t_base *base)
{
	int	l;
	int	i;

	l = ft_lstsize(base->groups);
	i = 0;
	while (i < l)
	{
		if (base->pid[i] != 0)
			kill(base->pid[i], SIGKILL);
		i++;
	}
	if (errno == 3)
		errno = 0;
	return (1);
}

int	is_builtin(t_group *group)
{
	if (group->arg == NULL)
		return (0);
	if ((ft_strncmp(group->arg_str[0], "cd", 3) == 0 || \
		ft_strncmp(group->arg_str[0], "echo", 5) == 0 || \
		ft_strncmp(group->arg_str[0], "pwd", 4) == 0 || \
		ft_strncmp(group->arg_str[0], "export", 7) == 0 || \
		ft_strncmp(group->arg_str[0], "unset", 6) == 0 || \
		ft_strncmp(group->arg_str[0], "env", 4) == 0 || \
		ft_strncmp(group->arg_str[0], "exit", 5) == 0))
		return (1);
	return (0);
}

int	null_program(t_group *group)
{
	return_fd_group(group);
	return (SUCCES);
}
