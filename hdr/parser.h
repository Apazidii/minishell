#ifndef PARSER_H
#define PARSER_H

#define VALID_ERROR 1
#define MALLOC_ERROR -1
#define SUCCES 0
#define END_OF_LEXER 2


int check_parenthesis(t_list *lexer);
void print_group(void *content);
int is_redirect(t_list *lexer);
char **arr_add_str(char **arr, char *str, int len_str);
void free_arr_str(char **arr);
int *add_arr_int(int *arr, int rep_var);


#endif