/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:39 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 18:36:26 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_word_separator(char c)
// {
// 	if (!c)
// 		return (1);
// 	if (c == ' ' || c == '\t')
// 		return (1);
// 	if (c == '|' || c == '<' || c == '>')
// 		return (1);
// 	return (0);
// }

// static char	*append_char_lexer(char *result, char c)
// {
// 	char	tmp[2];
// 	char	*joined;

// 	tmp[0] = c;
// 	tmp[1] = '\0';
// 	joined = ft_strjoin(result, tmp);
// 	free(result);
// 	return (joined);
// }

// static int	append_single_quote(char *line, int i, char **result)
// {
// 	i++;
// 	while (line[i] && line[i] != '\'')
// 	{
// 		if (line[i] == '$')
// 			*result = append_char_lexer(*result, PROTECTED_DOLLAR);
// 		else
// 			*result = append_char_lexer(*result, line[i]);
// 		i++;
// 	}
// 	if (line[i] == '\'')
// 		i++;
// 	return (i);
// }

// static int	append_double_quote(char *line, int i, char **result)
// {
// 	i++;
// 	while (line[i] && line[i] != '"')
// 	{
// 		*result = append_char_lexer(*result, line[i]);
// 		i++;
// 	}
// 	if (line[i] == '"')
// 		i++;
// 	return (i);
// }

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