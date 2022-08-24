/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 00:30:04 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/25 00:30:04 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lexer.h"
#include "minishell.h"

void	free_token(void *content)
{
	t_token	*c;

	c = (t_token *)content;
	free(c);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

char	*skip_spaces(char *s)
{
	while (is_space(*s))
		s++;
	return (s);
}

int	check_qutes(char *s)
{
	char	c;
	int		qo;

	qo = 0;
	while (*s != '\0')
	{
		if ((*s == '\'' || *s == '"'))
		{
			if (!qo)
			{
				c = *s;
				qo = 1;
			}
			else if (c == *s)
				qo = 0;
		}
		s++;
	}
	return (qo);
}
