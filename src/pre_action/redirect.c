#include <minishell.h>
#include <pre_action.h>

int straight_redirect(t_group *group, t_list *env, t_redirect *redirect, int number_redirect)
{
	int i;
	int fd;

	i = 0;
	if (number_redirect == 0)
	{
		group->buf_sr_fd = -2;
		return (SUCCES);
	}
	while(i < number_redirect)
	{
		if (insert_var(&(redirect[i].redirect_file), env) != SUCCES)
			return (MALLOC_ERROR);
		if (redirect[i].type_redirect == e_redirect)
			fd = open(redirect[i].redirect_file, O_CREAT | O_WRONLY | O_TRUNC,  0644);
		else if (redirect[i].type_redirect == e_double_redirect)
			fd = open(redirect[i].redirect_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(redirect[i].redirect_file);
			errno = 0;
			return (FILE_ERROR);
		}
		if (i != number_redirect - 1)
			close(fd);
		i++;
	}
	return (replace_fd(&group->buf_sr_fd, fd, 1));
}

int reverse_redirect(t_group *group, t_list *env, t_redirect *redirect, int number_redirect)
{
	int i;
	int fd;
	int error_code;

	i = 0;
	if (number_redirect == 0)
	{
		group->buf_rr_fd = -2;
		return (SUCCES);
	}
	while(i < number_redirect)
	{
		if (redirect[i].type_redirect != e_double_reverse_redirect)
			if (insert_var(&(redirect[i].redirect_file), env) != SUCCES)
				return (MALLOC_ERROR);
		if (redirect[i].type_redirect == e_reverse_redirect)
			fd = open(redirect[i].redirect_file, O_RDONLY,  0644);
		else if (redirect[i].type_redirect == e_double_reverse_redirect)
		{
			error_code = heredoc(&fd, redirect[i].redirect_file, env);
			if (error_code != SUCCES)
				return (error_code);
		}
		if (fd == -1)
		{
			perror(redirect[i].redirect_file);
			errno = 0;
			return (FILE_ERROR);
		}
		if (i != number_redirect - 1)
			close(fd);
		i++;
	}
	return (replace_fd(&group->buf_rr_fd, fd, 0));
}


int redirect(t_group *group, t_list *env)
{
	int error_code;

	error_code = straight_redirect(group, env, group->redirect, group->number_redirect);
	if (error_code != SUCCES)
		return (error_code);
	error_code = reverse_redirect(group, env, group->reverse_redirect, group->number_reverse_redirect);
	if (error_code != SUCCES)
		return (error_code);
	return (error_code);
}