/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:32:50 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 18:55:14 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exec_cmd(t_ast *node, t_input *input)
{
	char	*path;
	char	**env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (exec_redirs(node->cmd->redirs))
		exit(1);
	env = env_to_array(input->env);
	if (!env)
		exit(1);
	path = find_path(node->cmd->argv[0], env);
	if (!path)
		print_command_not_found(node->cmd->argv[0], env);
	execve(path, node->cmd->argv, env);
	exit_execve_error(node->cmd->argv[0], path, env);
}

static int	parent_wait_cmd(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	print_signal_message(status);
	return (status_from_wait(status));
}

int	exec_cmd(t_ast *node, t_input *input)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		child_exec_cmd(node, input);
	return (parent_wait_cmd(pid));
}
