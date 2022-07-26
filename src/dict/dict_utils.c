/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:29:21 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*parse_line_envp(char *line)
{
	t_dict	*res;
	int		i;

	res = (t_dict *)ft_calloc(sizeof(t_dict), 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '=')
		i++;
	res->key = ft_substr(line, 0, i);
	res->value = ft_substr(line, i + 1, ft_strlen(line));
	if (res->key == NULL || res->value == NULL)
	{
		if (res->key != NULL)
			free(res->key);
		if (res->value != NULL)
			free(res->value);
		free(res);
		perror("export");
		errno = 0;
		return (NULL);
	}
	return (res);
}

t_list	*parse_envp(char *envp[])
{
	int		i;
	t_list	*env_lst;

	if (envp == NULL)
		return (NULL);
	env_lst = ft_lstnew((void *) parse_line_envp(envp[0]));
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&env_lst, ft_lstnew((void *) parse_line_envp(envp[i])));
		i++;
		if (errno != 0)
			return (NULL);
	}
	return (env_lst);
}

void	free_dict(void *content)
{
	t_dict	*c;

	c = (t_dict *)content;
	if (c != NULL)
	{
		if (c->key != NULL)
			free(c->key);
		if (c->value != NULL)
			free(c->value);
	}
	free(c);
}
