/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:37:34 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 18:55:44 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_value(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

static char	*build_cmd_path(char *dir, char *cmd)
{
	char	*part;
	char	*full;

	part = ft_strjoin(dir, "/");
	if (!part)
		return (NULL);
	full = ft_strjoin(part, cmd);
	ft_free_str(part);
	return (full);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = build_cmd_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (full);
		ft_free_str(full);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*full;
	char	*path_value;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_value = get_path_value(env);
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	full = search_in_paths(paths, cmd);
	ft_free_tab(paths);
	return (full);
}
