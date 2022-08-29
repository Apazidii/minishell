/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:40:08 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "parser.h"

int	check_parenthesis(t_list *lexer)
{
	int	open;
	int	close;

	open = 0;
	close = 0;
	while (lexer)
	{
		if (((t_token *)lexer->content)->type == e_open_parenthesis)
			open++;
		if (((t_token *)lexer->content)->type == e_close_parenthesis)
			close++;
		lexer = lexer->next;
	}
	if (open == close)
		return (0);
	printf("Error: brackets are not closed\n");
	return (1);
}

int	check_pipe(t_list *lexer)
{
	while (lexer)
	{
		if (((t_token *)lexer->content)->type == e_pipe && \
			((t_token *)lexer->next->content)->type == e_newline)
		{
			printf("minishell: syntax error near unexpected token \'newline\'");
			return (1);
		}
		lexer = lexer->next;
	}
	return (0);
}

void	print_group(void *content)
{
	t_group	*group;
	int		i;

	group = (t_group *)content;
	i = 0;
	printf("------------------------------------------------\
	--------------------\n\n");
	printf("\t\t\tprogram: %s\n", group->arg[0].arg);
	printf("\t\t\targ: ");
	while (++i < group->number_arg)
		printf("%s ", group->arg[i].arg);
	printf("\n\n");
	if (group->number_redirect != 0)
	{
		printf("\t\t\tredirect:\n");
		i = 0;
		while (i < group->number_redirect)
		{
			printf("\t\t\t\ttype = %d file = %s\n", \
			group->redirect[i].type_redirect, group->redirect[i].redirect_file);
			i++;
		}
	}
	printf("\n");
	printf("------------------------------------------------\
	--------------------\n");
}
