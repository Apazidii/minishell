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
	t_list *arg;

	arg = group->arg;
	printf("------------------------------------------\n\n");
	printf("\t\t\tprogram: %.*s\n\n", ((t_token *)group->program->content)->len, ((t_token *)group->program->content)->token);
	printf("\t\t\targ: ");
	i = 0;
	while (i < group->number_arg)
	{
		printf("%.*s ", ((t_token *)arg->content)->len, ((t_token *)arg->content)->token);
		i++;
	}
	printf("\n\n");
	if (group->use_redirect)
		printf("\t\t\tredirect file: %.*s\n\n", ((t_token *)group->redirect_file->content)->len, ((t_token *)group->redirect_file->content)->token);
	printf("------------------------------------------\n");
}