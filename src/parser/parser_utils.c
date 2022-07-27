#include "minishell.h"
#include "parser.h"

int check_parenthesis(t_list *lexer)
{
	int open;
	int close;

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
	return (1);
}

void print_group(void *content)
{
	t_group	*group;
	int		i;

	group = (t_group *)content;

	printf("------------------------------------------\n\n");
	printf("\t\t\tprogram: %.*s\n\n", ((t_token *)group->program->content)->len, ((t_token *)group->program->content)->token);
	printf("\t\t\tnum of arg: %d\n", group->number_arg);
	printf("\t\t\targ: ");
	i = 0;
	while ((group->arg)[i])
	{
		printf("%s ", (group->arg)[i]);
		i++;
	}
	printf("\n\n");
	if (group->use_redirect)
		printf("\t\t\tredirect file: %.*s\n\n", ((t_token *)group->redirect_file->content)->len, ((t_token *)group->redirect_file->content)->token);
	printf("------------------------------------------\n");
}

int is_redirect(t_list *lexer)
{
	if (((t_token *) lexer->content)->type == e_redirect ||
		((t_token *) lexer->content)->type == e_reverse_redirect ||
		((t_token *) lexer->content)->type == e_double_redirect ||
		((t_token *) lexer->content)->type == e_double_reverse_redirect)
		return (1);
	return (0);
}

void free_group(void *gr)
{
	t_group  *group;

	group = (t_group *)gr;
	if (!group)
		return;
	if (!group->arg)
		return;
	free_arr_str(group->arg);
	free(group);
}
