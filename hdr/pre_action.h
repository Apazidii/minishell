/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_action.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:37:57 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/25 01:43:57 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRE_ACTION_H
# define PRE_ACTION_H

typedef struct s_group_env
{
	t_group	*group;
	t_list	*env;
}			t_group_env;

int		arg_in_arr_str(t_group *group, t_list *env);
int		run_command(t_group *group, t_base *base);
int		run_exec(t_base *base, char *bin, char **arg);
int		apply_fork(t_group *group, t_base *base, int i);
int		is_builtin(t_group *group);

void	close_heredoc(int i, int number_redirect, int fd, t_group *group);
int		run_straight_redirect(t_redirect *redirect, \
	int i, t_list *env, int *fd);
int		run_reverse_redirect(t_redirect *redirect, \
	int i, t_group_env ge, int *fd);
int		redirect_repvar(t_redirect *redirect, int i, t_list *env);
int		redirect(t_group *group, t_list *env);
int		heredoc(int *f, char *stop, t_list *env, t_group *group);
int		init_pipe(t_list *gr1, t_list *gr2, t_base *base);

int		replace_fd(int *buf_fd, int fd, int newfd);
void	return_fd(int buf_fd, int fd);
int		replace_fd_group(t_group *group);
void	return_fd_group(t_group *group);

void	close_unused_fd(t_group *group);

#endif