#ifndef MINISHELL_H
# define MINISHELL_H


# include "../src/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


enum e_type
{
	e_pipe,
	e_redirect,
	e_reverse_redirect,
	e_double_redirect,
	e_double_reverse_redirect,
	e_open_parenthesis,
	e_close_parenthesis,
	e_and,
	e_or,
	e_str
};

typedef struct s_dict
{
	char *key;
	char *value;
}		t_dict;

typedef struct s_token
{
	char	*token;
	int 	len;
	enum	e_type type;
	int		rep_var;
}			t_token;

typedef struct s_base
{
	t_list	*env_lst;
	t_list	*lexer;
	char	*command;
}			t_base;


//lexer
int lexer(char *command, t_base *base);
void free_token(void *content);

//parse lst and lst utils
t_list *parse_envp(char *envp[]);
void print_content(void *content);
void free_dict(void *content);


#endif