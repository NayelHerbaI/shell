/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:30:14 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/25 18:02:16 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	builtin_echo(t_ast *node)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (node->cmd->argv[1] && !ft_strncmp(node->cmd->argv[1], "-n", 3))
	{
		newline = 0;
		i = 2;
	}
	while (node->cmd->argv[i])
	{
		ft_putstr_fd(node->cmd->argv[i], STDOUT_FILENO);
		if (node->cmd->argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT_FILENO);
}

static void	builtin_env(t_input *input)
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
}

void	exec_builtin(t_ast *node, t_input *input)
{
	char	*cmd;

	cmd = node->cmd->argv[0];
	if (!ft_strncmp(cmd, "echo", 5))
		builtin_echo(node);
	else if (!ft_strncmp(cmd, "pwd", 4))
		builtin_pwd();
	else if (!ft_strncmp(cmd, "env", 4))
		builtin_env(input);
	else if (!ft_strncmp(cmd, "cd", 3))
		builtin_cd(node);
	else if (!ft_strncmp(cmd, "unset", 6))
		builtin_unset(node, input);
	else if (!ft_strncmp(cmd, "exit", 5))
		exit(0);
}
