/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:43:53 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/14 14:59:56 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (quote == 0 && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote != 0 && line[i] == quote)
			quote = 0;
		i++;
	}
	if (quote != 0)
	{
		ft_putstr_fd(SYNTAX_ERROR_QUOTE, STDERR_FILENO);
		return (2);
	}
	return (0);
}

int	is_redir_token(int type)
{
	if (type == INREDIR || type == OUTREDIR
		|| type == APPOUTREDIR || type == HEREDOC)
		return (1);
	return (0);
}

int	check_syntax(t_lexbuf *tokens)
{
	t_lexbuf	*curr;

	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
		return (ft_putstr_fd(SYNTAX_ERROR_PIPE, STDERR_FILENO), 2);
	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (!curr->next || curr->next->type == PIPE)
				return (ft_putstr_fd(SYNTAX_ERROR_PIPE, STDERR_FILENO), 2);
		}
		else if (is_redir_token(curr->type))
		{
			if (!curr->next || curr->next->type != WORD)
				return (ft_putstr_fd(SYNTAX_ERROR_NEWLINE, STDERR_FILENO), 2);
		}
		curr = curr->next;
	}
	return (0);
}
