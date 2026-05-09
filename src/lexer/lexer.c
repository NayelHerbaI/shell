/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:45 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:16:09 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_token(t_lexbuf **tokens, t_lexbuf *to_remove)
{
	if (!to_remove)
		return ;
	if (to_remove->prev)
		to_remove->prev->next = to_remove->next;
	else
		*tokens = to_remove->next;
	if (to_remove->next)
		to_remove->next->prev = to_remove->prev;
	free(to_remove->value);
	free(to_remove);
}

void	merge_joined_tokens(t_lexbuf **tokens)
{
	t_lexbuf	*curr;
	t_lexbuf	*next;
	char		*joined;

	if (!tokens || !*tokens)
		return ;
	curr = *tokens;
	while (curr && curr->next)
	{
		if (curr->type == WORD && curr->join_next
			&& curr->next->type == WORD)
		{
			next = curr->next;
			joined = ft_strjoin(curr->value, next->value);
			if (!joined)
				return ;
			free(curr->value);
			curr->value = joined;
			curr->join_next = next->join_next;
			remove_token(tokens, next);
		}
		else
			curr = curr->next;
	}
}

t_lexbuf	*lexer(char *line)
{
	t_lexbuf	*tokens;
	int			i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = lex_squote(line, i, &tokens);
		else if (line[i] == '"')
			i = lex_dquote(line, i, &tokens);
		else if (line[i] == '|')
			i = lex_pipe(line, i, &tokens);
		else if (line[i] == '>' || line[i] == '<')
			i = lex_redir(line, i, &tokens);
		else if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
			i = lex_word(line, i, &tokens);
	}
	return (tokens);
}
