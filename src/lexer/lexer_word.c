/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:39 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:15:44 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_word(char *line, int i, t_lexbuf **tokens)
{
	int		start;
	char	*word;

	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '|' && line[i] != '<' && line[i] != '>'
		&& line[i] != '\'' && line[i] != '"')
		i++;
	if (i == start)
		return (i + 1);
	word = ft_substr(line, start, i - start);
	add_token(tokens, word, WORD);
	ft_free_str(word);
	set_last_join_next(*tokens, is_word_join_char(line[i]));
	return (i);
}
