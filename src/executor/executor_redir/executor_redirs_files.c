/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirs_files.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 19:58:25 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 19:59:25 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_redir_error(char *file)
{
	perror(file);
	return (1);
}

int	apply_input_redir(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (print_redir_error(redir->file));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	apply_output_redir(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (print_redir_error(redir->file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_append_redir(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (print_redir_error(redir->file));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redir(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (apply_input_redir(redir));
	if (redir->type == REDIR_OUT)
		return (apply_output_redir(redir));
	if (redir->type == REDIR_APPEND)
		return (apply_append_redir(redir));
	if (redir->type == REDIR_HEREDOC)
		return (apply_heredoc(redir));
	return (0);
}
