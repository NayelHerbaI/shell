/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:56:28 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:18:41 by hnayel           ###   ########.fr       */
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

int	is_var_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (!joined)
		return (NULL);
	free(s1);
	free(s2);
	return (joined);
}

char	*expand_exit_value(char *value, t_input *input, int *i)
{
	char	*status;

	status = ft_itoa(input->exit_status);
	value = join_and_free(value, status);
	*i += 2;
	return (value);
}

char	*expand_env_var(char *word, char *result, t_input *input, int *i)
{
	int		start;
	char	*key;
	char	*value;

	(*i)++;
	start = *i;
	while (word[*i] && is_var_char(word[*i]))
		(*i)++;
	key = ft_substr(word, start, *i - start);
	value = get_env_value(input->env, key);
	free(key);
	result = join_and_free(result, ft_strdup(value));
	return (result);
}
