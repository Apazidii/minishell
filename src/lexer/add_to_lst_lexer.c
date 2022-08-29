/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_lst_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:29:57 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "lexer.h"

int	add_to_lst_lexer(t_token *token, t_list **lexer)
{
	t_list	*new;

	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(lexer, new);
	return (SUCCES);
}
