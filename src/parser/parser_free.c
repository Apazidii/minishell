/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:40:23 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "parser.h"

int	free_group_arg(t_arg *arg, int num_arg)
{
	int	i;

	if (arg != NULL)
	{
		i = -1;
		while (++i < num_arg)
			if (arg[i].arg != NULL)
				free(arg[i].arg);
		free(arg);
	}
	return (1);
}

int	free_group_arg_str(char **arg, int num_arg)
{
	int	i;

	if (arg != NULL)
	{
		i = -1;
		while (++i < num_arg)
			if (arg[i] != NULL)
				free(arg[i]);
		free(arg);
	}
	return (1);
}

int	free_group_redirect(t_redirect *arg, int num_arg)
{
	int	i;

	if (arg != NULL)
	{
		i = -1;
		while (++i < num_arg)
			if (arg[i].redirect_file != NULL)
				free(arg[i].redirect_file);
		free(arg);
	}
	return (1);
}

void	free_group_list(void *content)
{
	free_group(content);
}

int	free_group(t_group *group)
{
	if (group == NULL)
		return (1);
	if (group->number_redirect > 0)
		free_group_redirect(group->redirect, group->number_redirect);
	if (group->number_reverse_redirect > 0)
		free_group_redirect(group->reverse_redirect,
			group->number_reverse_redirect);
	if (group->number_arg > 0)
		free_group_arg(group->arg, group->number_arg);
	if (group->arg_str != NULL)
		free_group_arg_str(group->arg_str, group->number_arg);
	free(group);
	return (1);
}
