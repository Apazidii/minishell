#ifndef MINISHELL_H
# define MINISHELL_H


# include "../src/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_dict
{
	char *key;
	char *value;
}		t_dict;



//parse lst and lst utils
t_list *parse_envp(char *envp[]);
void print_content(void *content);
void free_lst(t_list *lst);



#endif