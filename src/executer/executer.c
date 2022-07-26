/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 21:53:17 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "executer.h"

int	run_exec(t_base *base, char *bin, char **arg)
{
	char	*pbin;
	int		error_code;

	error_code = find_bin(base->env_lst, bin, &pbin);
	if (error_code != SUCCES)
		return (error_code);
	if (execve(pbin, arg, base->env_arr) == -1)
	{
		perror(pbin);
		errno = 0;
		return (EXEC_ERROR);
	}
	return (SUCCES);
}
