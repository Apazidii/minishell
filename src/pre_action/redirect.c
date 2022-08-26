/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:53:01 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <minishell.h>
#include <pre_action.h>

int	straight_redirect(t_group *group, t_list *env, \
	t_redirect *redirect, int number_redirect)
{
	int		i;
	int		fd;
	int		error_code;

	i = 0;
	if (number_redirect == 0)
	{
		group->buf_sr_fd = -2;
		return (SUCCES);
	}
	while (i < number_redirect)
	{
		error_code = run_straight_redirect(redirect, i, env, &fd);
		if (error_code != SUCCES)
			return (error_code);
		group->type_redirect = redirect[i].type_redirect;
		if (i != number_redirect - 1)
			close(fd);
		i++;
	}
	return (replace_fd(&group->buf_sr_fd, fd, 1));
}

int	reverse_redirect(t_group *group, t_list *env,
	t_redirect *redirect, int number_redirect)
{
	int			i;
	int			fd;
	int			error_code;
	t_group_env	ge;

	i = 0;
	if (number_redirect == 0)
		group->buf_rr_fd = -2;
	if (number_redirect == 0)
		return (SUCCES);
	ge.env = env;
	ge.group = group;
	while (i < number_redirect)
	{
		error_code = run_reverse_redirect(redirect, i, ge, &fd);
		if (error_code != SUCCES)
			return (error_code);
		close_heredoc(i, number_redirect, fd, group);
		i++;
	}
	return (replace_fd(&group->buf_rr_fd, fd, 0));
}

int	redirect(t_group *group, t_list *env)
{
	int	error_code;

	error_code = straight_redirect(group, env, group->redirect,
			group->number_redirect);
	if (error_code != SUCCES)
		return (error_code);
	error_code = reverse_redirect(group, env, \
	group->reverse_redirect, group->number_reverse_redirect);
	if (error_code != SUCCES)
		return (error_code);
	return (error_code);
}
