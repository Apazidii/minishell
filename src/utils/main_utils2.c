/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:38:31 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/25 02:58:09 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../hdr/minishell.h"

int	free_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (1);
}

int	free_one(void *k)
{
	free(k);
	return (1);
}

int	add_exit_code(t_list **list)
{
	t_dict	*d;

	d = (t_dict *) ft_calloc(sizeof(t_dict), 1);
	if (d == NULL)
	{
		perror("add_env");
		return (MALLOC_ERROR);
	}
	d->key = ft_strdup("?");
	d->value = ft_itoa(0);
	ft_lstadd_back(list, ft_lstnew(d));
	return (SUCCES);
}

int	change_exit_code(t_list *list, int exit_code)
{
	t_dict	*c;

	while (list)
	{
		c = list->content;
		if (ft_strncmp(c->key, "?", 2) == 0)
		{
			free(c->value);
			c->value = ft_itoa(exit_code);
			return (SUCCES);
		}
		list = list->next;
	}
	return (NOT_FOUND);
}
