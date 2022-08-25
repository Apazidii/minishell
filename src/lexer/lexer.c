/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:30:00 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/25 00:30:00 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "lexer.h"

int	manager_lexer(char **command, t_list **lexer)
{
	if (is_space(**command))
		*command = skip_spaces(*command);
	if (**command == '|')
		return (pipe_or_lexer(command, lexer));
	if (**command == '>')
		return (redirect_lexer(command, lexer));
	if (**command == '<')
		return (reverse_redirect_lexer(command, lexer));
	if (**command == '\'' || **command == '"')
		return (quote_lexer(command, lexer));
	if (**command != '\0')
		return (str_lexer(command, lexer));
	return (SUCCES);
}

int	lexer(char *command, t_base *base)
{
	t_list	*lexer;
	t_list	*nl;

	lexer = NULL;
	if (check_qutes(command))
	{
		ft_putendl_fd("Error: Quotation marks are not closed", 2);
		return (VALID_ERROR);
	}
	while (*command != '\0')
	{
		if (manager_lexer(&command, &lexer))
			return (MALLOC_ERROR);
	}
	nl = ft_lstlast(lexer);
	((t_token *)(nl->content))->type = e_newline;
	base->lexer = lexer;
	return (SUCCES);
}
