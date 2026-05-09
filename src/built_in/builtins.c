/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:30:14 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 18:14:11 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (1);
}

int	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4)
		|| !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

int	pick_builtin(t_ast *node, t_input *input, char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (builtin_echo(node, input));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(cmd, "env", 4))
		return (builtin_env(input));
	else if (!ft_strncmp(cmd, "cd", 3))
		return (builtin_cd(node));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (builtin_unset(node, input));
	else if (!ft_strncmp(cmd, "export", 7))
		return (builtin_export(node, input));
	else
		return (0);
}

int	exec_builtin(t_ast *node, t_input *input)
{
	char	*cmd;
	int		saved_stdin;
	int		saved_stdout;
	int		status;

	if (save_fds(&saved_stdin, &saved_stdout))
		return (1);
	if (exec_redirs(node->cmd->redirs))
		return (restore_fds(saved_stdin, saved_stdout));
	cmd = node->cmd->argv[0];
	if (!ft_strncmp(cmd, "exit", 5))
		return (handle_exit_builtin(node, input, saved_stdin, saved_stdout));
	status = pick_builtin(node, input, cmd);
	restore_fds(saved_stdin, saved_stdout);
	return (status);
}
