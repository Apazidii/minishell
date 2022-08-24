/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:36:10 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/24 17:36:10 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **arg, int num_arg)
{
	if (num_arg != 2)
		printf("minishell: cd: too many arguments");
	if (chdir(arg[1]) == -1)
	{
		printf("cd: %s: %s\n", arg[1], strerror(errno));
		errno = 0;
		return (BUILTIN_ERROR);
	}
	return (SUCCES);
}
