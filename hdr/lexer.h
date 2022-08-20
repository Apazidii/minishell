#ifndef LEXER_H
#define LEXER_H

#include "minishell.h"

void print_lexer(void *content);
char *skip_spaces(char *s);
int check_qutes(char *s);
int is_metachar(char c);
int is_space(char c);

int	pipe_or_lexer(char **command, t_list **lexer);
int	redirect_lexer(char **command, t_list **lexer);
int	reverse_redirect_lexer(char **command, t_list **lexer);
int	str_lexer(char **command, t_list **lexer);
int	quote_lexer(char **command, t_list **lexer);

int add_to_lst_lexer(t_token *token, t_list **lexer);

#endif
