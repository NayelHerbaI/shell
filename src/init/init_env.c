/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:33:37 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 17:43:33 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_creating_error(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (NULL);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!envp || !envp[0])
		return (NULL);
	env = NULL;
	i = 0;
	while (envp[i])
	{
		new = add_new(envp[i]);
		if (!new)
			return (env_creating_error(env));
		add_back(&env, new);
		i++;
	}
	return (env);
}
