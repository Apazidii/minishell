#ifndef PARSER_H
#define PARSER_H

#define VALID_ERROR 1
#define MALLOC_ERROR -1
#define SUCCES 0
#define END_OF_LEXER 2

int check_parenthesis(t_list *lexer);
int	manager_redirect(t_list **lexer, t_group *group);
int free_group(t_group *group);
int parse_arg(t_list **lexer, t_group *group);
int free_group_arg(t_arg *arg, int num_arg);
void free_group_list(void *content);

void print_group(void *gr);


#endif