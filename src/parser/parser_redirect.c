#include "minishell.h"
#include "parser.h"

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

	group->redirect_file = ft_substr(((t_token *)(*lexer)->content)->token, 0, ((t_token *)(*lexer)->content)->len);
	if (group->redirect_file == NULL)
	{
		free_group(group);
		return (MALLOC_ERROR);
	}
	*lexer = (*lexer)->next;
	return (SUCCES);

}

int reverse_redirect_parser(t_list **lexer, t_group *group)
{
	t_token *c;

	c = (t_token *)(*lexer)->content;
	group->type_reverse_redirect = c->type;
	group->use_reverse_redirect = 1;
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
	group->reverse_redirect_file = ft_substr(((t_token *)(*lexer)->content)->token, 0, ((t_token *)(*lexer)->content)->len);
	if (group->reverse_redirect_file == NULL)
	{
		free_group(group);
		return (MALLOC_ERROR);
	}
	*lexer = (*lexer)->next;
	return (SUCCES);
}

int redirect_manager(t_list **lexer, t_group *group)
{
	t_token *c;

	c = (t_token *)(*lexer)->content;
	if (c->type == e_reverse_redirect || c->type == e_double_reverse_redirect)
		return (reverse_redirect_parser(lexer, group));
	return (redirect_parser(lexer, group));
}