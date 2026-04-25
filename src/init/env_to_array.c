/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 17:40:10 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/25 17:41:42 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*env_join_line(char *key, char *value)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	if (value)
		line = ft_strjoin(tmp, value);
	else
		line = ft_strdup(tmp);
	free(tmp);
	return (line);
}

static void	free_env_array_partial(char **envp, int filled)
{
	while (filled > 0)
	{
		filled--;
		free(envp[filled]);
	}
	free(envp);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = env_join_line(env->key, env->value);
		if (!envp[i])
		{
			free_env_array_partial(envp, i);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
