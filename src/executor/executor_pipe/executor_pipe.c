/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:50 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 19:04:23 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_pipe_children(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	print_signal_message(status2);
	return (status_from_wait(status2));
}

int	exec_pipe(t_ast *node, t_input *input)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) < 0)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (close_pipe_error(fd));
	if (pid1 == 0)
		exec_left_pipe_child(node, input, fd);
	pid2 = fork();
	if (pid2 < 0)
	{
		close_pipe_error(fd);
		waitpid(pid1, NULL, 0);
		return (1);
	}
	if (pid2 == 0)
		exec_right_pipe_child(node, input, fd);
	close(fd[0]);
	close(fd[1]);
	return (wait_pipe_children(pid1, pid2));
}
