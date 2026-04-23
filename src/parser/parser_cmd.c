/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:53 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 14:03:32 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_lexbuf *tok)
{
	int count;

	count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD)
			count++;
		tok = tok->next;
	}
	return (count);
}

static void	add_redir(t_cmd *cmd, t_redir_type type, char *file)
{
	t_redir *redir;
	t_redir *last;

	redir = new_redir(type, file);
	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = redir;
}

t_ast	*parse_command(t_lexbuf **tok)
{
	t_ast   *node;
	int     argc;
	int     i;

	node = new_ast(AST_CMD);
	node->cmd = new_cmd();
	argc = count_args(*tok);
	node->cmd->argv = ft_calloc(argc + 1, sizeof(char *));
	i = 0;
	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type == WORD)
			node->cmd->argv[i++] = ft_strdup((*tok)->value);
		else if ((*tok)->type == INREDIR && (*tok)->next)
		{
			*tok = (*tok)->next;
			add_redir(node->cmd, REDIR_IN, (*tok)->value);
		}
		else if ((*tok)->type == OUTREDIR && (*tok)->next)
		{
			*tok = (*tok)->next;
			add_redir(node->cmd, REDIR_OUT, (*tok)->value);
		}
		else if ((*tok)->type == APPOUTREDIR && (*tok)->next)
		{
			*tok = (*tok)->next;
			add_redir(node->cmd, REDIR_APPEND, (*tok)->value);
		}
		else if ((*tok)->type == HEREDOC && (*tok)->next)
		{
			*tok = (*tok)->next;
			add_redir(node->cmd, REDIR_HEREDOC, (*tok)->value);
		}
		*tok = (*tok)->next;
	}
	return (node);
}
