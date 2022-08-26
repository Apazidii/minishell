/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:37:04 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/26 14:41:48 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "pre_action.h"

char	*create_filename(char *s, int i)
{
	char	*num;
	char	*res;

	num = ft_itoa(i);
	if (num == NULL)
		return (NULL);
	res = ft_strjoin(s, num);
	free(num);
	return (res);
}

int	write_heredoc(char *stop, int fd, t_list *env)
{
	char		*temp;
	char		*s;

	while (1)
	{
		s = readline("> ");
		if (s == NULL)
			break ;
		if (ft_strncmp(s, stop, ft_strlen(stop) + 1) == 0)
			break ;
		temp = s;
		if (insert_var(&s, env) != SUCCES)
		{
			free(s);
			close(fd);
			return (MALLOC_ERROR);
		}
		free(temp);
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
	}
	if (s != NULL)
		free(s);
	return (SUCCES);
}

int	heredoc(int *f, char *stop, t_list *env, t_group *group)
{
	int			fd;
	static int	i;

	group->heredoc_filename = create_filename(group->arg_str[0], i++);
	if (group->heredoc_filename == NULL)
		return (MALLOC_ERROR);
	fd = open(group->heredoc_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		errno = 0;
		return (FILE_ERROR);
	}
	if (write_heredoc(stop, fd, env) != SUCCES)
		return (MALLOC_ERROR);
	close(fd);
	fd = open(group->heredoc_filename, O_RDONLY, 0644);
	*f = fd;
	return (SUCCES);
}
