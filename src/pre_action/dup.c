#include "minishell.h"
#include "pre_action.h"


void return_fd(int buf_fd, int fd)
{
	if (buf_fd != -2)
	{
		if (dup2(buf_fd, fd) == -1)
		{
			close(buf_fd);
			perror("dup2");
			return ;
		}
		close(buf_fd);
	}
}


int replace_fd(int *buf_fd, int fd, int newfd)
{
	if (fd == -2)
		return (SUCCES);
	*buf_fd = dup(newfd);
	if (*buf_fd == -1)
	{
		close(fd);
		perror("dup");
		errno = 0;
		return (DUP_ERROR);
	}
	if (dup2(fd, newfd) == -1)
	{
		close(fd);
		perror("dup2");
		errno = 0;
		return (DUP_ERROR);
	}
	close(fd);
	return (SUCCES);
}

void close_unused_fd(t_group *group)
{
	if (group->pipe_input[1] != 0)
		close(group->pipe_input[1]);
	else
		group->pipe_input[0] = -2;
	if (group->pipe_output[0] != 0)
		close(group->pipe_output[0]);
	else
		group->pipe_output[1] = -2;
	group->pipe_input[1] = -2;
	group->pipe_output[0] = -2;
}

int replace_fd_group(t_group *group)
{
	int error_code;

	error_code = replace_fd(&(group->pipe_input_buf),  group->pipe_input[0],   0);
	if (error_code == SUCCES)
		error_code = replace_fd(&(group->pipe_output_buf), group->pipe_output[1] , 1);
	return (error_code);
}

int return_fd_group(t_group *group)
{
	return_fd(group->buf_sr_fd, 1);
	return_fd(group->buf_rr_fd, 0);
	return_fd(group->pipe_input_buf, 0);
	return_fd(group->pipe_output_buf, 1);
}