#include "minishell.h"
#include "lexer.h"



int pipe_or_lexer(char **command, t_list **lexer)
{
	t_token *token;
	t_list	*new;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (1);
	token->token = *command;
	if (*((*command) + 1) == '|')
	{
		token->type = e_or;
		token->len = 2;
		*command += 2;
	}
	else
	{
		token->type = e_pipe;
		token->len = 1;
		*command += 1;
	}
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lexer, new);
	return (0);
}

int redirect_lexer(char **command, t_list **lexer)
{
	t_token *token;
	t_list	*new;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (1);
	token->token = *command;
	if (*((*command) + 1) == '>')
	{
		token->type = e_double_redirect;
		token->len = 2;
		*command += 2;
	}
	else
	{
		token->type = e_redirect;
		token->len = 1;
		*command += 1;
	}
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lexer, new);
	return (0);
}

int reverse_redirect_lexer(char **command, t_list **lexer)
{
	t_token *token;
	t_list	*new;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (1);
	token->token = *command;
	if (*((*command) + 1) == '<')
	{
		token->type = e_double_reverse_redirect;
		token->len = 2;
		*command += 2;
	}
	else
	{
		token->type = e_reverse_redirect;
		token->len = 1;
		*command += 1;
	}
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lexer, new);
	return (0);
}

int and_lexer(char **command, t_list **lexer)
{
	t_token *token;
	t_list	*new;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (1);
	token->token = *command;
	if (*((*command) + 1) == '&')
	{
		token->type = e_and;
		token->len = 2;
		*command += 2;
	}
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lexer, new);
	return (0);
}

int parenthesis_lexer(char **command, t_list **lexer)
{
	t_token *token;
	t_list	*new;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (1);
	token->token = *command;
	if (**command == '(')
	{
		token->type = e_open_parenthesis;
		token->len = 1;
		*command += 1;
	}
	else if (**command == ')')
	{
		token->type = e_close_parenthesis;
		token->len = 1;
		*command += 1;
	}
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lexer, new);
	return (0);
}

int str_lexer(char **command, t_list **lexer)
{
	t_token *token;
	t_list	*new;
	int 	i;

	i = 0;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (1);
	token->token = *command;
	while (!is_metachar((*command)[i]) && !is_space((*command)[i]) && (*command)[i] != '\0')
	{
		if ((*command)[i] == '&' && (*command)[i + 1] == '&')
			break;
		i++;
	}
	token->len = i;
	token->type = e_str;
	*command = &(*command)[i];
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lexer, new);
	return (0);
}

int quote_lexer(char **command, t_list **lexer)
{
	t_token *token;
	t_list	*new;
	int 	i;
	char	c;

	i = 0;
	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (1);
	c = **command;
	(*command)++;
	token->token = *command;
	token->rep_var = 1;
	if (c == '\'')
		token->rep_var = 0;
	while ((*command)[i] != c && (*command)[i] != '\0')
		i++;
	token->len = i;
	token->type = e_str;
	*command = &(*command)[i + 1];
	new = ft_lstnew((void *)token);
	if (!new)
	{
		free(token);
		return (1);
	}
	ft_lstadd_back(lexer, new);
	return (0);
}

int manager_lexer(char **command, t_list **lexer)
{
	if (is_space(**command))
		*command = skip_spaces(*command);
	if (**command == '|')
		return (pipe_or_lexer(command, lexer));
	if (**command == '>')
		return (redirect_lexer(command, lexer));
	if (**command == '<')
		return (reverse_redirect_lexer(command, lexer));
	if (**command == '(' || **command == ')')
		return (parenthesis_lexer(command, lexer));
	if (**command == '&' && *((*command) + 1) == '&')
		return (and_lexer(command, lexer));
	if (**command == '\'' || **command == '"')
		return (quote_lexer(command, lexer));
	return (str_lexer(command, lexer));
}

int lexer(char *command, t_base *base)
{
	t_list *lexer;

	lexer = NULL;
	if (check_qutes(command))
	{
		printf("Error: Quotation marks are not closed\n");
		return (2);
	}
	while (*command != '\0')
	{
		if (manager_lexer(&command, &lexer))
			return (1);
	}
	base->lexer = lexer;
//	ft_lstiter(lexer, print_token);
	return (0);
}

