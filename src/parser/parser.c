/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:55 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 14:08:27 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*parse_pipeline(t_lexbuf **tok)
{
	t_ast	*left;
	t_ast	*pipe_node;

	left = parse_command(tok);
	if (*tok && (*tok)->type == PIPE)
	{
		*tok = (*tok)->next;
		pipe_node = new_ast(AST_PIPE);
		pipe_node->left = left;
		pipe_node->right = parse_pipeline(tok);
		return (pipe_node);
	}
	return (left);
}

t_ast	*parser(t_lexbuf *tokens)
{
	return (parse_pipeline(&tokens));
}
