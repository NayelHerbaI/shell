/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:50:40 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/04 16:07:20 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*expand_word(char *word, t_input *input)
{
	char	*value;

	if (!word)
		return (NULL);
	if (!ft_strcmp(word, "$?"))
		return (ft_itoa(input->exit_status));
	if (word[0] == '$' && word[1])
	{
		value = get_env_value(input->env, &word[1]);
		return (ft_strdup(value));
	}
	return (ft_strdup(word));
}

void	expand_tokens(t_lexbuf *tokens, t_input *input)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			expanded = expand_word(tokens->value, input);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}
