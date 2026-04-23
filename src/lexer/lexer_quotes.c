/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:43 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 13:43:14 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_squote(char *line, int i, t_lexbuf **tokens)
{
	int		start;
	char	*word;

	i++;
	start = i;
	while (line[i] && line[i] != '\'')
		i++;
	word = ft_substr(line, start, i - start);
	add_token(tokens, word, WORD);
	ft_free_str(word);
	if (line[i] == '\'')
		i++;
	return (i);
}

int	lex_dquote(char *line, int i, t_lexbuf **tokens)
{
	int		start;
	char	*word;

	i++;
	start = i;
	while (line[i] && line[i] != '"')
		i++;
	word = ft_substr(line, start, i - start);
	add_token(tokens, word, WORD);
	ft_free_str(word);
	if (line[i] == '"')
		i++;
	return (i);
}
