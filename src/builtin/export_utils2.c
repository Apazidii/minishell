/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:37:21 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "builtin.h"

void	*copy_dict(void *content)
{
	t_dict	*d;
	t_dict	*c;

	d = (t_dict *) ft_calloc(sizeof(t_dict), 1);
	if (d == NULL)
		return (NULL);
	c = (t_dict *)content;
	d->key = ft_strdup(c->key);
	if (d->key == NULL && c->key != NULL)
	{
		free_dict(d);
		return (NULL);
	}
	d->value = ft_strdup(c->value);
	if (d->value == NULL && c->value != NULL)
	{
		free_dict(d);
		return (NULL);
	}
	return (d);
}

int	export(char **arg, int num_arg, t_base *base)
{
	int		i;
	t_list	*temp;

	if (num_arg == 1)
	{
		temp = ft_lstmap(base->env_lst, copy_dict, free_dict);
		if (temp == NULL)
		{
			perror("export");
			errno = 0;
			return (MALLOC_ERROR);
		}
		sort_list(temp);
		ft_lstiter(temp, print_env);
		ft_lstclear(&temp, free_dict);
	}
	i = 1;
	while (i < num_arg)
	{
		if (add_env(arg[i], base) != SUCCES)
			return (MALLOC_ERROR);
		i++;
	}
	return (SUCCES);
}
