/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 15:37:47 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:14:11 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_interrupt(int fd[2], int saved_stdin)
{
	close(fd[0]);
	close(fd[1]);
	restore_heredoc_stdin(saved_stdin);
	return (130);
}

void	restore_heredoc_stdin(int saved_stdin)
{
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

int	init_heredoc(int fd[2], int *saved_stdin)
{
	g_signal = 0;
	*saved_stdin = dup(STDIN_FILENO);
	if (*saved_stdin < 0)
		return (1);
	if (pipe(fd) == -1)
	{
		close(*saved_stdin);
		return (1);
	}
	signal(SIGINT, signal_here_doc);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	read_one_heredoc(t_redir *redir)
{
	int		fd[2];
	int		saved_stdin;
	char	*line;

	if (init_heredoc(fd, &saved_stdin) != 0)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (handle_heredoc_interrupt(fd, saved_stdin));
		if (!line)
			break ;
		if (!ft_strcmp(line, redir->file))
		{
			free(line);
			break ;
		}
		write_heredoc_line(line, fd[1]);
	}
	close(fd[1]);
	restore_heredoc_stdin(saved_stdin);
	redir->heredoc_fd = fd[0];
	return (0);
}
