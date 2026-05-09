/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:53 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:25:16 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redir(t_cmd *cmd, t_redir_type type, char *file)
{
	t_redir	*redir;
	t_redir	*last;

	redir = new_redir(type, file);
	if (!redir)
		return ;
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

static int	token_to_redir_type(int token_type)
{
	if (token_type == INREDIR)
		return (REDIR_IN);
	if (token_type == OUTREDIR)
		return (REDIR_OUT);
	if (token_type == APPOUTREDIR)
		return (REDIR_APPEND);
	if (token_type == HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

static int	is_redir_parser_token(int token_type)
{
	if (token_type == INREDIR || token_type == OUTREDIR
		|| token_type == APPOUTREDIR || token_type == HEREDOC)
		return (1);
	return (0);
}

static void	parse_redir_token(t_lexbuf **tok, t_cmd *cmd)
{
	int	redir_type;

	redir_type = token_to_redir_type((*tok)->type);
	*tok = (*tok)->next;
	add_redir(cmd, redir_type, (*tok)->value);
}

t_ast	*parse_command(t_lexbuf **tok)
{
	t_ast	*node;
	int		argc;
	int		i;

	node = new_ast(AST_CMD);
	node->cmd = new_cmd();
	argc = count_args(*tok);
	node->cmd->argv = ft_calloc(argc + 1, sizeof(char *));
	i = 0;
	while (*tok && (*tok)->type != PIPE)
	{
		if ((*tok)->type == WORD)
			node->cmd->argv[i++] = ft_strdup((*tok)->value);
		else if (is_redir_parser_token((*tok)->type) && (*tok)->next)
			parse_redir_token(tok, node->cmd);
		*tok = (*tok)->next;
	}
	return (node);
}
