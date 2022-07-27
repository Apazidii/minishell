#ifndef PARSER_H
#define PARSER_H

#define VALID_ERROR 1
#define MALLOC_ERROR -1
#define SUCCES 0
#define END_OF_LEXER 2

typedef struct s_group
{
	t_list		*program;

	char 		**arg;
	int			number_arg;

	int			use_redirect;
	enum e_type	type_redirect;
	t_list		*redirect_file;

	int 		pipe_input;
	int 		pipe_output;
}			t_group;

int check_parenthesis(t_list *lexer);
void print_group(void *content);
int is_redirect(t_list *lexer);
char **arr_add_str(char **arr, char *str, int len_str);
void free_arr_str(char **arr);
void free_group(void *gr);


#endif