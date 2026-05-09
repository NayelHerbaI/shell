/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_execve_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:40:00 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 18:55:54 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_command_not_found(char *cmd, char **env)
{
	free_env_array(env);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(COMMAND_NOT_FOUND, STDERR_FILENO);
	exit(127);
}

void	exit_execve_error(char *cmd, char *path, char **env)
{
	int	err;

	err = errno;
	perror(cmd);
	ft_free_str(path);
	free_env_array(env);
	if (err == EACCES || err == EISDIR || err == ENOEXEC)
		exit(126);
	if (err == ENOENT)
		exit(127);
	exit(1);
}
