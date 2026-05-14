/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:50:40 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/13 11:37:38 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *value, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(value, tmp);
	if (!joined)
		return (NULL);
	free(value);
	return (joined);
}

char	*expand_word(char *word, t_input *input)
{
	char	*value;
	int		i;

	if (!word)
		return (NULL);
	i = 0;
	value = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '?')
			value = expand_exit_value(value, input, &i);
		else if (word[i] == '$' && word[i + 1] && is_var_char(word[i + 1]))
			value = expand_env_var(word, value, input, &i);
		else
		{
			value = append_char(value, word[i]);
			i++;
		}
	}
	return (value);
}

void	expand_tokens(t_lexbuf *tokens, t_input *input)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == WORD && tokens->quote_type != QUOTE_SINGLE)
		{
			expanded = expand_word(tokens->value, input);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}

int	count_args(t_lexbuf *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != PIPE)
	{
		if (tok->type == WORD)
			count++;
		tok = tok->next;
	}
	return (count);
}
