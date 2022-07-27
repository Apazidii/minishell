#include "minishell.h"
#include "parser.h"


//syntax error near unexpected token "&&"

int redirect_parser(t_list **lexer, t_group *group)
{
	t_token *c;

	c = (t_token *)(*lexer)->content;
	group->type_redirect = c->type;
	group->use_redirect = 1;
	*lexer = (*lexer)->next;
	if (*lexer == NULL)
	{
		printf("minishell: syntax error near unexpected token \"newline\"\n");
		return (VALID_ERROR);
	}
	c = (t_token *)(*lexer)->content;
	if (c->type != e_str)
	{
		printf("minishell: syntax error near unexpected token \"%.*s\"\n", c->len, c->token);
		return (VALID_ERROR);
	}
	group->redirect_file = *lexer;
	*lexer = (*lexer)->next;
	return (SUCCES);

}

int group_parser(t_list **lex, t_group **gr)
{
	t_token *c;
	t_list *lexer;
	t_group *group;
	int 	i;

	lexer = *lex;
	if (!lexer)
		return (END_OF_LEXER);
	c = (t_token *)lexer->content;
	if (c->type != e_str)
	{
		printf("minishell: syntax error near unexpected token \"%.*s\"\n", c->len, c->token);
		return (VALID_ERROR);
	}
	group = (t_group *) ft_calloc(sizeof(t_group), 1);
	if (!group)
		return (MALLOC_ERROR);
	group->arg = (char **) ft_calloc(sizeof(char *), 1);
	(group->arg)[0] == NULL;
	group->program = lexer;
	lexer = lexer->next;
	i = 0;
	while (lexer != NULL && ((t_token *)lexer->content)->type != e_pipe)
	{
		if (is_redirect(lexer))
		{
			if (redirect_parser(&lexer, group) != SUCCES)
			{
				free_group(group);
				return (VALID_ERROR);
			}
		}
		else
		{
			group->arg = arr_add_str(group->arg, ((t_token *)lexer->content)->token, ((t_token *)lexer->content)->len);
			if (group->arg == NULL)
			{
				free_group(group);
				return (MALLOC_ERROR);
			}
			i++;
			lexer = lexer->next;
		}
	}
	group->number_arg = i;
	if (lexer != NULL)
	{
		group->pipe_output = 1;
		lexer = lexer->next;
	}
	*lex = lexer;
	*gr = group;
	return (SUCCES);
}

int parser(t_list *lexer, t_base *base)
{
	t_list *all_groups;
	t_group *group;

	if (check_parenthesis(lexer))
	{
		printf("Error: brackets are not closed\n");
		return (2);
	}
	all_groups = NULL;
	while (lexer != NULL)
	{
		if (group_parser(&lexer, &group) != SUCCES)
		{
			ft_lstclear(&all_groups, free_group);
			return (-1);
		}
		ft_lstadd_back(&all_groups, ft_lstnew(group));
	}
	ft_lstiter(all_groups, print_group);
}