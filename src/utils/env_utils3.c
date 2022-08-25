/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:39:34 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/24 17:39:34 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../hdr/minishell.h"

void	copy_from_dest(char *dest, char **res, size_t *i)
{
	*i = 0;
	while (dest[*i] != '\0')
	{
		(*res)[*i] = dest[*i];
		(*i)++;
	}
}

void	get_status(char **key, char **res, size_t *i, t_list *env)
{
	*key = find_in_env(env, "?");
	*res = ft_strnconcat(*res, *key, 0, ft_strlen(*key));
	*i += 2;
}
