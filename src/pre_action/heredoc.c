#include "minishell.h"
#include "pre_action.h"

int heredoc(int *f, char *stop, t_list *env)
{
	int fd;
	char *s;

	fd = open("/tmp", __O_TMPFILE | O_RDWR);
	if (fd == -1)
	{
		perror("heredoc");
		errno = 0;
		return (FILE_ERROR);
	}
	while (1)
	{
		s = readline("> ");
		if (ft_strncmp(s, stop, ft_strlen(stop) + 1) == 0)
			break;
		if (insert_var(&s, env) != SUCCES)
		{
			free(s);
			close(fd);
			return (MALLOC_ERROR);
		}
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
	}
	free(s);
	*f = fd;
	return (SUCCES);
}