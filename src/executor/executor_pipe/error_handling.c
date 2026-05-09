/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 19:02:04 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 19:04:51 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	close_pipe_error(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (1);
}

void	exec_left_pipe_child(t_ast *node, t_input *input, int fd[2])
{
	int	status;

	setup_pipe_child_signals();
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	status = executor(node->left, input);
	close_heredoc_fds(node);
	exit(status);
}

void	exec_right_pipe_child(t_ast *node, t_input *input, int fd[2])
{
	int	status;

	setup_pipe_child_signals();
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	status = executor(node->right, input);
	close_heredoc_fds(node);
	exit(status);
}
