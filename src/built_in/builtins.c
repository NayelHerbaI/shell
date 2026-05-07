/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:30:14 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 14:27:09 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	restore_fds(int saved_stdin, int saved_stdout)
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


static int	builtin_pwd(void)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

static int	builtin_env(t_input *input)
{
	t_env	*curr;

	curr = input->env;
	while (curr)
	{
		ft_putstr_fd(curr->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		if (curr->value)
			ft_putstr_fd(curr->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		curr = curr->next;
	}
	return (0);
}

int	exec_builtin(t_ast *node, t_input *input)
{
	char	*cmd;
	int		saved_stdin;
	int		saved_stdout;
	int		status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		return (1);
	if (exec_redirs(node->cmd->redirs))
		return (restore_fds(saved_stdin, saved_stdout));
	cmd = node->cmd->argv[0];
	if (!ft_strncmp(cmd, "echo", 5))
		status = (builtin_echo(node, input));
	else if (!ft_strncmp(cmd, "pwd", 4))
		status = (builtin_pwd());
	else if (!ft_strncmp(cmd, "env", 4))
		status = (builtin_env(input));
	else if (!ft_strncmp(cmd, "cd", 3))
		status = (builtin_cd(node));
	else if (!ft_strncmp(cmd, "unset", 6))
		status = (builtin_unset(node, input));
	else if (!ft_strncmp(cmd, "export", 7))
		status = (builtin_export(node, input));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (builtin_exit(node, input));
	else
		status = 0;	
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}
