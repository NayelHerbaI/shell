/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:33:51 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 14:02:17 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd(redir->file, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_OUT)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == REDIR_APPEND)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	exec_redirs(t_redir *redir)
{
	while (redir)
	{
		apply_redir(redir);
		redir = redir->next;
	}
}
