/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:36:01 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/24 17:36:01 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	print_env_without_declare(void *content)
{
	t_dict	*c;

	c = (t_dict *)content;
	if (ft_strncmp(c->key, "?", 2) == 0)
		return ;
	if (c->value != NULL)
		printf("%s=%s\n", c->key, c->value);
}

int	env(t_base *base)
{
	ft_lstiter(base->env_lst, print_env_without_declare);
	return (SUCCES);
}
