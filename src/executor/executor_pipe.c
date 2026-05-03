/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:50 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/03 14:26:56 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_ast *node, t_input *input)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (pipe(fd) < 0)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(executor(node->left, input));
	}
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(executor(node->right, input));
	}
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFSIGNALED(status2) && WTERMSIG(status2) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (WIFSIGNALED(status2) && WTERMSIG(status2) == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	return (status_from_wait(status2));
}

// int	exec_pipe(t_ast *node, t_input *input)
// {
// 	int		fd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (pipe(fd) < 0)
// 		return (0);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		exit(executor(node->left, input));
// 		exit(0);
// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		exit(executor(node->right, input));
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }
