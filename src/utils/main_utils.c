/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:39:29 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_space_string(char *s)
{
	while (*s != '\0')
	{
		if (*s != ' ')
			return (1);
		s++;
	}
	return (0);
}

char	*add_newline(char *cmd)
{
	char	*res;

	res = ft_strjoin(cmd, " newline");
	free(cmd);
	if (!res)
		return (NULL);
	return (res);
}

char	*get_promt(t_base *base)
{
	char	*res;
	char	*str;

	if (get_cwd(base))
		return (NULL);
	str = ft_strjoin("\033[0;35mminishell\033[0m:\033[0;36m", base->cwd);
	res = ft_strjoin(str, "\033[0m$ ");
	free(str);
	if (res == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	*read_cmd(t_base *base, int *eof)
{
	char	*s;
	char	*promt;

	*eof = 0;
	promt = get_promt(base);
	if (promt == NULL)
		return (NULL);
	s = readline(promt);
	free(promt);
	if (s == NULL)
	{
		*eof = 1;
		return (NULL);
	}
	if (is_space_string(s))
		add_history(s);
	return (s);
}

int	get_cwd(t_base *base)
{
	if (getcwd(base->cwd, PATH_MAX) == NULL)
	{
		perror(strerror(errno));
		errno = 0;
		return (1);
	}
	return (0);
}
