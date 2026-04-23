/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:42 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 13:42:25 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_redir(char *line, int i, t_lexbuf **tokens)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		add_token(tokens, ">>", APPOUTREDIR);
		return (i + 2);
	}
	if (line[i] == '<' && line[i + 1] == '<')
	{
		add_token(tokens, "<<", HEREDOC);
		return (i + 2);
	}
	if (line[i] == '>')
	{
		add_token(tokens, ">", OUTREDIR);
		return (i + 1);
	}
	add_token(tokens, "<", INREDIR);
	return (i + 1);
}

int	lex_pipe(char *line, int i, t_lexbuf **tokens)
{
	(void)line;
	add_token(tokens, "|", PIPE);
	return (i + 1);
}
