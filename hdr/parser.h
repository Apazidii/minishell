#ifndef PARSER_H
#define PARSER_H

void set_pipe(t_list *group);
int check_pipe(t_list *lexer);
int check_parenthesis(t_list *lexer);
int	manager_redirect(t_list **lexer, t_group *group);
int free_group(t_group *group);
int parse_arg(t_list **lexer, t_group *group);
int free_group_arg(t_arg *arg, int num_arg);
void free_group_list(void *content);

void print_group(void *gr);


#endif