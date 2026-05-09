/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:18:17 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:14:40 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_heredocs(t_ast *node)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == AST_CMD)
		return (prepare_cmd_heredocs(node));
	if (node->type == AST_PIPE)
	{
		status = prepare_heredocs(node->left);
		if (status != 0)
			return (status);
		return (prepare_heredocs(node->right));
	}
	return (0);
}

int	prepare_cmd_heredocs(t_ast *node)
{
	t_redir	*redir;
	int		status;

	if (!node || !node->cmd)
		return (0);
	redir = node->cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			status = read_one_heredoc(redir);
			if (status != 0)
				return (status);
		}
		redir = redir->next;
	}
	return (0);
}

int	apply_heredoc(t_redir *redir)
{
	if (redir->heredoc_fd < 0)
		return (1);
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
		return (1);
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (0);
}

void	write_heredoc_line(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
}
