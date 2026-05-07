/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:40 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 18:26:49 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_join_next(t_lexbuf *tokens, int join_next)
{
	t_lexbuf	*last;

	if (!tokens)
		return ;
	last = tokens;
	while (last->next)
		last = last->next;
	last->join_next = join_next;
}

int	is_word_join_char(char c)
{
	if (!c)
		return (0);
	if (c == ' ' || c == '\t')
		return (0);
	if (c == '|' || c == '<' || c == '>')
		return (0);
	return (1);
}

void	set_last_quote_type(t_lexbuf *tokens, int quote_type)
{
	t_lexbuf	*last;

	if (!tokens)
		return ;
	last = tokens;
	while (last->next)
		last = last->next;
	last->quote_type = quote_type;
}

t_lexbuf	*add_token(t_lexbuf **tokens, char *value, int type)
{
	t_lexbuf	*new;
	t_lexbuf	*last;

	new = malloc(sizeof(t_lexbuf));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	new->env = NULL;
	new->input = NULL;
	new->quote_type = QUOTE_NONE;
	new->join_next = 0;
	if (!*tokens)
	{
		*tokens = new;
		return (new);
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	return (new);
}
