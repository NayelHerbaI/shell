/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:18:17 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/03 12:30:25 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_one_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, redir->file))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
	redir->heredoc_fd = fd[0];
	return (0);
}

static int	prepare_cmd_heredocs(t_ast *node)
{
	t_redir	*redir;

	if (!node || !node->cmd)
		return (0);
	redir = node->cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			if (read_one_heredoc(redir) != 0)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

int	prepare_heredocs(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
	{
		if (prepare_heredocs(node->left) != 0)
			return (1);
		if (prepare_heredocs(node->right) != 0)
			return (1);
	}
	else if (node->type == AST_CMD)
	{
		if (prepare_cmd_heredocs(node) != 0)
			return (1);
	}
	return (0);
}
