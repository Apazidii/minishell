/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:40:15 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/24 17:40:15 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "parser.h"

int	unexpected_token(t_list **lexer)
{
	if (((t_token *)((*lexer)->content))->type == e_newline
		|| ((t_token *)((*lexer)->content))->type == e_pipe)
	{
		printf("minishell: syntax error near unexpected token \'%.*s\'\n", \
		((t_token *)((*lexer)->content))->len, \
		((t_token *)((*lexer)->content))->token);
		return (VALID_ERROR);
	}
	return (SUCCES);
}

int	group_parser(t_list **lexer, t_group **gr)
{
	int	error_code;

	*gr = (t_group *) ft_calloc(sizeof(t_group), 1);
	if (*gr == NULL)
		return (MALLOC_ERROR);
	if (unexpected_token(lexer) != SUCCES)
		return (VALID_ERROR);
	while (((t_token *)((*lexer)->content))->type != e_newline
		&& ((t_token *)((*lexer)->content))->type != e_pipe)
	{
		error_code = parse_redirect(lexer, *gr);
		if (error_code != SUCCES)
			return (error_code);
		error_code = parse_arg(lexer, *gr);
		if (error_code != SUCCES)
			return (error_code);
	}
	group_argue(&(*gr));
	*lexer = (*lexer)->next;
	return (SUCCES);
}

void	group_argue(t_group **gr)
{
	(*gr)->pipe_input_buf = -2;
	(*gr)->pipe_output_buf = -2;
	(*gr)->pipe_input[0] = -2;
	(*gr)->pipe_input[1] = -2;
	(*gr)->pipe_output[0] = -2;
	(*gr)->pipe_output[1] = -2;
}

int	parser(t_list *lexer, t_base *base)
{
	t_group	*group;
	t_list	*all_groups;
	int		error_code;

	all_groups = NULL;
	if (check_parenthesis(lexer))
		return (2);
	while (lexer != NULL)
	{
		error_code = group_parser(&lexer, &group);
		if (error_code != SUCCES)
		{
			ft_lstclear(&all_groups, free_group_list);
			return (error_code);
		}
		ft_lstadd_back(&all_groups, ft_lstnew((void *)group));
	}
	base->groups = all_groups;
	return (SUCCES);
}
