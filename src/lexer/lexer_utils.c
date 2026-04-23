/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:40 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 13:41:24 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
