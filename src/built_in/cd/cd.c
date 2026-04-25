/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:24:26 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/25 16:51:22 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_path(t_ast *node)
{
	char	*path;

	if (!node->cmd->argv[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		if (chdir(path) == -1)
			perror("cd");
		return (1);
	}
	return (0);
}

int	check_tilde_path(char *path)
{
	char	*home_path;

	home_path = NULL;
	if (!ft_strncmp(path, "~/", 2))
	{
		home_path = getenv("HOME");
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		if (chdir(home_path) == -1)
			perror("cd");
		if (chdir(&path[2]) == -1)
			perror("cd");
		return (1);
	}
	return (0);
}

void	builtin_cd(t_ast *node)
{
	char	*path;

	if (empty_path(node))
		return ;
	path = node->cmd->argv[1];
	if (check_tilde_path(path))
		return ;
	if (!ft_strcmp("~", path))
		path = getenv("HOME");
	if (chdir(path) == -1)
		perror("cd");
}
