#include "minishell.h"
#include "parser.h"


int group_parser(t_list **lexer, t_group **gr)
{
	int error_code;
	t_group *group;

	group = *gr;
	group = (t_group *) ft_calloc(sizeof(t_group), 1);
	if (group == NULL)
		return (MALLOC_ERROR);
	while (((t_token *)((*lexer)->content))->type != e_newline && ((t_token *)((*lexer)->content))->type != e_pipe)
	{
		error_code = manager_redirect(lexer, group);
		if (error_code != SUCCES)
			return (error_code);
		error_code = parse_arg(lexer, group);
		if (error_code != SUCCES)
			return (error_code);
	}
	if (((t_token *)((*lexer)->content))->type == e_pipe)
	{
		group->pipe_output = 1;
		*lexer = (*lexer)->next;
	}
	*gr = group;
	return (SUCCES);
}

int parser(t_list *lexer, t_base *base)
{
	t_group *group;
	t_list	*all_groups;
	int		error_code;

	all_groups = NULL;
	if (check_parenthesis(lexer))
		return (2);
	if (check_pipe(lexer))
		return (2);
	while (((t_token *)lexer->content)->type != e_newline)
	{
		error_code = group_parser(&lexer, &group);
		if (error_code != SUCCES)
		{
			free_group(group);
			ft_lstclear(&all_groups, free_group_list);
			return (error_code);
		}
		ft_lstadd_back(&all_groups, ft_lstnew((void *)group));
	}
	set_pipe(all_groups);
	base->groups = all_groups;
//	ft_lstiter(all_groups, print_group);
	return (SUCCES);
}