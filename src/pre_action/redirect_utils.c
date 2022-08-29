/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:34:42 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "pre_action.h"

void	close_heredoc(int i, int number_redirect, int fd, t_group *group)
{
	if (i != number_redirect - 1)
	{
		close(fd);
		if (group->type_reverse_redirect == e_double_reverse_redirect)
		{
			unlink(group->heredoc_filename);
			free(group->heredoc_filename);
		}
	}
}

int	run_straight_redirect(t_redirect *redirect, int i, t_list *env, int *fd)
{
	if (redirect_repvar(redirect, i, env) != SUCCES)
		return (MALLOC_ERROR);
	if (redirect[i].type_redirect == e_redirect)
		*fd = open(redirect[i].redirect_file, O_CREAT \
		| O_WRONLY | O_TRUNC, 0644);
	else if (redirect[i].type_redirect == e_double_redirect)
		*fd = open(redirect[i].redirect_file, O_CREAT \
		| O_WRONLY | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror(redirect[i].redirect_file);
		errno = 0;
		return (FILE_ERROR);
	}
	return (SUCCES);
}

int	run_reverse_redirect(t_redirect *redirect, int i, t_group_env ge, int *fd)
{
	int	error_code;

	if (redirect[i].type_redirect != e_double_reverse_redirect)
	{
		if (redirect_repvar(redirect, i, ge.env) != SUCCES)
			return (MALLOC_ERROR);
	}
	if (redirect[i].type_redirect == e_reverse_redirect)
		*fd = open(redirect[i].redirect_file, O_RDONLY, 0644);
	else if (redirect[i].type_redirect == e_double_reverse_redirect)
	{
		error_code = heredoc(fd, redirect[i].redirect_file, ge.env, ge.group);
		if (error_code != SUCCES)
			return (error_code);
	}
	if (*fd == -1)
	{
		perror(redirect[i].redirect_file);
		errno = 0;
		return (FILE_ERROR);
	}
	ge.group->type_reverse_redirect = redirect[i].type_redirect;
	return (SUCCES);
}

int	redirect_repvar(t_redirect *redirect, int i, t_list *env)
{
	char	*temp;


	temp = redirect[i].redirect_file;
	if (insert_var(&(redirect[i].redirect_file), env, redirect[i].rep_var) != SUCCES)
		return (MALLOC_ERROR);
	free(temp);
	return (SUCCES);
}
