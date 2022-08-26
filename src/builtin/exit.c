/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:35:30 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtint_exit(t_base *base)
{
	ft_lstclear(&base->lexer, free_token);
	ft_lstclear(&base->groups, free_group_list);
	free(base->command);
	rl_clear_history();
	ft_lstclear(&base->env_lst, free_dict);
	exit(0);
}
