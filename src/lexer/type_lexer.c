/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:30:08 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "lexer.h"

int	pipe_or_lexer(char **command, t_list **lexer)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (MALLOC_ERROR);
	token->token = *command;
	token->type = e_pipe;
	token->len = 1;
	*command += 1;
	return (add_to_lst_lexer(token, lexer));
}

int	redirect_lexer(char **command, t_list **lexer)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (MALLOC_ERROR);
	token->token = *command;
	if (*((*command) + 1) == '>')
	{
		token->type = e_double_redirect;
		token->len = 2;
		*command += 2;
	}
	else
	{
		token->type = e_redirect;
		token->len = 1;
		*command += 1;
	}
	return (add_to_lst_lexer(token, lexer));
}

int	reverse_redirect_lexer(char **command, t_list **lexer)
{
	t_token	*token;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (MALLOC_ERROR);
	token->token = *command;
	if (*((*command) + 1) == '<')
	{
		token->type = e_double_reverse_redirect;
		token->len = 2;
		*command += 2;
	}
	else
	{
		token->type = e_reverse_redirect;
		token->len = 1;
		*command += 1;
	}
	return (add_to_lst_lexer(token, lexer));
}

int	str_lexer(char **command, t_list **lexer)
{
	t_token	*token;
	int		i;

	i = 0;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (MALLOC_ERROR);
	token->token = *command;
	while (!is_metachar((*command)[i]) && \
			!is_space((*command)[i]) && (*command)[i] != '\0')
		i++;
	token->len = i;
	token->rep_var = 1;
	token->type = e_str;
	*command = &(*command)[i];
	return (add_to_lst_lexer(token, lexer));
}

int	quote_lexer(char **command, t_list **lexer)
{
	t_token	*token;
	int		i;
	char	c;

	i = 0;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (MALLOC_ERROR);
	c = **command;
	(*command)++;
	token->token = *command;
	token->rep_var = 1;
	if (c == '\'')
		token->rep_var = 0;
	while ((*command)[i] != c && (*command)[i] != '\0')
		i++;
	token->len = i;
	token->type = e_str;
	*command = &(*command)[i + 1];
	return (add_to_lst_lexer(token, lexer));
}
