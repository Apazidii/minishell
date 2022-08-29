/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalactu <dgalactu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:37:41 by dgalactu          #+#    #+#             */
/*   Updated: 2022/08/29 16:54:11 by dgalactu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	sigint_fork_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
}

void	sigquit_fork_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3\n", 2);
}

void	newline_sig_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 1);
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	set_interactive_mode_signals(void)
{
	signal(SIGINT, newline_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_fork_signals(void)
{
	signal(SIGINT, sigint_fork_handler);
	signal(SIGQUIT, sigquit_fork_handler);
}
