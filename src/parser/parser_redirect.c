#include "minishell.h"
#include "parser.h"

int parse_redirect(t_list **lexer, t_group *group, t_redirect *redirect)
{
	t_token *content;

	content = ((t_token *)(*lexer)->content);
	redirect->use_redirect = 1;
	redirect->type_redirect = content->type;
	*lexer = (*lexer)->next;
	content = ((t_token *)(*lexer)->content);
	if (content->type != e_str)
	{
		printf("minishell: syntax error near unexpected token \'%.*s\'\n", content->len, content->token);
		return (VALID_ERROR);
	}
	redirect->redirect_file = ft_substr(content->token, 0, content->len);
	if (redirect->redirect_file == NULL && free_group(group))
		return (MALLOC_ERROR);
	*lexer = (*lexer)->next;
	return (SUCCES);
}

int	manager_redirect(t_list **lexer, t_group *group)
{
	if (((t_token *)(*lexer)->content)->type == e_redirect || \
		((t_token *)(*lexer)->content)->type == e_double_redirect)
		return (parse_redirect(lexer, group, &group->redirect));
	if (((t_token *)(*lexer)->content)->type == e_reverse_redirect || \
		((t_token *)(*lexer)->content)->type == e_double_reverse_redirect)
		return (parse_redirect(lexer, group, &group->reverse_redirect));
	return (SUCCES);
}