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
	e_newline,
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
	t_list	*groups;
	char	*command;
}			t_base;



typedef struct s_arg
{
	char	*arg;
	int		rep_var;
}			t_arg;

typedef struct s_redirect
{
	int			use_redirect;
	enum e_type	type_redirect;
	char		*redirect_file;
}				t_redirect;

typedef struct s_group
{
	char		*program;

	t_arg		*arg;
	int			number_arg;

	t_redirect redirect;
	t_redirect reverse_redirect;

	int 		pipe_input;
	int 		pipe_output;
}			t_group;



//parser
int parser(t_list *lexer, t_base *base);
void free_group_list(void *content);
//void free_group(void *gr);

//lexer
int lexer(char *command, t_base *base);
void free_token(void *content);
void print_token(void *content);

//parse lst and lst utils
t_list *parse_envp(char *envp[]);
void print_content(void *content);
void free_dict(void *content);


#endif