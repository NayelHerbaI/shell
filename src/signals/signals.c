/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:49 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 14:04:49 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_readline(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_done = 1;
}

void	signal_readline2(int signum)
{
	(void)signum;
	g_signal = SIGQUIT;
}

void	signal_pipex(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	signal_here_doc(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	ft_putchar_fd('\n', STDOUT_FILENO);
	close(STDIN_FILENO);
}
