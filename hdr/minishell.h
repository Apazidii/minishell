/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:25:54 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/24 17:22:26 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../src/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>
# include <signal.h>

# define MALLOC_ERROR	42
# define DIR_NOT_FOUND	127
# define EXEC_ERROR		126
# define FORK_ERROR		10
# define ENV_NOT_FOUND	1
# define DIR_ERROR		1
# define NOT_FOUND		404
# define FILE_ERROR		2
# define DUP_ERROR		1
# define PIPE_ERROR		1
# define END_OF_LEXER	1
# define BUILTIN_ERROR	2
# define VALID_ERROR		2
# define SUCCES			0
# define STOP			-1

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
	char	*key;
	char	*value;
}		t_dict;

typedef struct s_token
{
	char		*token;
	int			len;
	enum e_type	type;
	int			rep_var;
}			t_token;

typedef struct s_base
{
	t_list	*env_lst;
	char	**env_arr;
	int		exit_status;
	t_list	*lexer;
	t_list	*groups;
	pid_t	*pid;
	char	*command;
	char	cwd[PATH_MAX];
}			t_base;

typedef struct s_arg
{
	char	*arg;
	int		rep_var;
}			t_arg;

typedef struct s_redirect
{
	int			rep_var;
	enum e_type	type_redirect;
	char		*redirect_file;
}				t_redirect;

typedef struct s_group
{
	t_arg		*arg;
	char		**arg_str;
	int			number_arg;
	t_redirect	*redirect;
	int			number_redirect;
	enum e_type	type_redirect;
	t_redirect	*reverse_redirect;
	char		*heredoc_filename;
	int			number_reverse_redirect;
	enum e_type	type_reverse_redirect;
	int			fd_redirect;
	int			fd_reverse_redirect;
	int			buf_sr_fd;
	int			buf_rr_fd;
	int			use_fork;
	int			pipe_input_buf;
	int			pipe_input[2];
	int			pipe_output_buf;
	int			pipe_output[2];
}			t_group;

//executer
int		executer(t_group *group, t_base *base);

//builtin
int		echo(char **arg, int num_arg);
int		pwd(t_base *base);
int		cd(char **arg, int num_arg);
int		builtint_exit(t_base *base);
int		export(char **arg, int num_arg, t_base *base);
int		unset(char **arg, int num_arg, t_base *base);
int		env(t_base *base);

//pre_action
int		chech_builtin(t_group *group, t_base *base);
int		pre_action(t_base *base);
int		kill_pid(t_base *base);

//parser
int		parser(t_list *lexer, t_base *base);

//lexer
int		lexer(char *command, t_base *base);
void	free_group_list(void *content);
void	free_token(void *content);
void	print_token(void *content);

//parse lst and lst utils
t_list	*parse_envp(char *envp[]);
void	print_content(void *content);
void	free_dict(void *content);

//main
char	*read_cmd(t_base *base, int *eof);
int		get_cwd(t_base *base);
int		is_space_string(char *s);
char	*add_newline(char *cmd);

int		insert_var(char **str, t_list *env);

//env
char	*find_in_env(t_list *env, char *key);
t_dict	*find_dict_in_env(t_list *env, char *key);
t_dict	*parse_line_envp(char *line);
void	checks_and_init(size_t *i, char **res);
char	*iterate_per_perem(size_t *i, size_t *start, char *str);
void	get_last_dollar(size_t *i, char *str, char **res);
void	get_remaining_characters(size_t *start, size_t *i, \
	char *str, char **res);
char	*ft_strnconcat(char *dest, char *src, size_t start, size_t end);
char	*get_perem(char *str, size_t start, size_t end);
int		add_exit_code(t_list **list);
int		change_exit_code(t_list *list, int exit_code);

void	copy_from_dest(char *dest, char **res, size_t *i);
//signal
void	set_interactive_mode_signals(void);
void	set_fork_signals(void);
void	set_ignore_signals(void);

//free
int		free_arr(char **s);
int		free_one(void *k);

#endif