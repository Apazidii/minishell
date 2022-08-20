#include "minishell.h"
#include "lexer.h"

int	add_to_lst_lexer(t_token *token, t_list **lexer)
{
	t_list	*new;

	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(lexer, new);
	return (SUCCES);
}
