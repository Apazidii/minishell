/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:36:10 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **arg, int num_arg)
{
	if (num_arg != 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (BUILTIN_ERROR);
	}
	if (chdir(arg[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(" ", 2);
		ft_putendl_fd(strerror(errno), 2);
		errno = 0;
		return (BUILTIN_ERROR);
	}
	return (SUCCES);
}
