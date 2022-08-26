/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:29:05 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pre_action.h"

int	init_pipe(t_list *gr1, t_list *gr2, t_base *base)
{
	int		fds[2];
	t_group	*group1;
	t_group	*group2;

	if (gr2 == NULL)
		return (SUCCES);
	if (ft_lstsize(base->groups) == 1)
		return (SUCCES);
	group1 = (t_group *)gr1->content;
	group2 = (t_group *)gr2->content;
	if (pipe(fds) == -1)
	{
		perror("pipe");
		errno = 0;
		return (PIPE_ERROR);
	}
	group1->pipe_output[0] = fds[0];
	group1->pipe_output[1] = fds[1];
	group2->pipe_input[0] = fds[0];
	group2->pipe_input[1] = fds[1];
	return (SUCCES);
}
