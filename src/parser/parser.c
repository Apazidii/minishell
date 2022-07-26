#include "minishell.h"


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

int	group_parser()
{

}

int parser(t_list *lexer, t_base *base)
{
	if (check_parenthesis(lexer))
	{
		printf("Error: brackets are not closed\n");
		return (2);
	}

}