/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 22:58:38 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "executer.h"

int	get_path(t_list *env, char ***res)
{
	char	*s;
	char	*path;

	s = find_in_env(env, "PATH");
	if (s == NULL)
		return (ENV_NOT_FOUND);
	path = ft_strdup(s);
	if (path == NULL)
	{
		free(s);
		return (MALLOC_ERROR);
	}
	*res = ft_split(path, ':');
	free(path);
	if (*res == NULL)
	{
		free(s);
		return (MALLOC_ERROR);
	}
	return (SUCCES);
}

int	check_bin_path(DIR *dir, char *bin)
{
	struct dirent	*dent;
	int				k;

	dent = readdir(dir);
	while (dent)
	{
		if (dent->d_type == 8)
		{
			k = ft_strncmp(dent->d_name, bin, ft_strlen(bin) + 1);
			if (k == 0)
			{
				closedir(dir);
				return (SUCCES);
			}
		}
		dent = readdir(dir);
	}
	return (DIR_NOT_FOUND);
}

int	check_bin(char *path, char *bin)
{
	DIR				*dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		ft_putendl_fd("Dir error", 2);
		return (DIR_ERROR);
	}
	if (check_bin_path(dir, bin) == SUCCES)
		return (SUCCES);
	closedir(dir);
	if (errno != 0)
	{
		perror("closedir");
		errno = 0;
		return (DIR_ERROR);
	}
	return (DIR_NOT_FOUND);
}

int	check_path(char **path_arr, char *bin, int *i)
{
	int	error_code;

	*i = 0;
	while (path_arr[*i])
	{
		error_code = check_bin(path_arr[*i], bin);
		if (error_code == DIR_ERROR && free_arr(path_arr))
			return (error_code);
		if (error_code == SUCCES)
			break ;
		(*i)++;
	}
	return (error_code);
}

int	find_bin(t_list *env, char *bin, char **res)
{
	int		error_code;
	char	**path_arr;
	char	*path;
	int		i;

	error_code = get_path(env, &path_arr);
	if (error_code != SUCCES)
		return (error_code);
	error_code = check_path(path_arr, bin, &i);
	if (error_code == DIR_ERROR)
		return (error_code);
	if (error_code == DIR_NOT_FOUND && free_arr(path_arr))
	{
		*res = bin;
		return (SUCCES);
	}
	path = ft_strjoin(path_arr[i], "/");
	*res = ft_strjoin(path, bin);
	free(path);
	if (*res == NULL && free_arr(path_arr))
		return (MALLOC_ERROR);
	free_arr(path_arr);
	return (SUCCES);
}
