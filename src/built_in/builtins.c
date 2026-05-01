/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:30:14 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/01 14:05:52 by hnayel           ###   ########.fr       */
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


static int	builtin_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
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

	cmd = node->cmd->argv[0];
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
	else if (!ft_strncmp(cmd, "exit", 5))
		exit(0);
	return (0);
}
