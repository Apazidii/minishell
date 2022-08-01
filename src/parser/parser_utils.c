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
	t_group *group = (t_group *)content;
	int		i;

	i = 0;
	printf("--------------------------------------------------------------------\n\n");
	printf("\t\t\tprogram: %s\n", group->arg[0].arg);
	printf("\t\t\targ: ");
	while (++i < group->number_arg)
		printf("%s ", group->arg[i].arg);
	printf("\n\n");
	if (group->redirect.use_redirect)
		printf("\t\t\tredirect file: %s\n", group->redirect.redirect_file);
	if (group->reverse_redirect.use_redirect)
		printf("\t\t\treverse redirect file: %s\n", group->reverse_redirect.redirect_file);
	printf("\n");
	printf("--------------------------------------------------------------------\n");
}