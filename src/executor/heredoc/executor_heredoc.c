/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:18:17 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 15:35:19 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_one_heredoc(t_redir *redir)
{
	int		fd[2];
	int		saved_stdin;
	char	*line;

	g_signal = 0;
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (1);
	if (pipe(fd) == -1)
	{
		close(saved_stdin);
		return (1);
	}
	signal(SIGINT, signal_here_doc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
		{
			close(fd[0]);
			close(fd[1]);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			return (130);
		}
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
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	redir->heredoc_fd = fd[0];
	return (0);
}

static int	prepare_cmd_heredocs(t_ast *node)
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

int	prepare_heredocs(t_ast *node)
{
	int	status;

	if (!node)
		return (0);
	if (node->type == AST_PIPE)
	{
		status = prepare_heredocs(node->left);
		if (status != 0)
			return (status);
		status = prepare_heredocs(node->right);
		if (status != 0)
			return (status);
	}
	else if (node->type == AST_CMD)
	{
		status = prepare_cmd_heredocs(node);
		if (status != 0)
			return (status);
	}
	return (0);
}
