/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:15:31 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 18:16:33 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_doesnt_exist(char *var, t_input *input)
{
	if (!var)
		return ;
	add_back(&input->env, add_new(var));
}

int	var_already_exists(char *var, t_input *input)
{
	t_env	*curr;
	char	*key;

	curr = input->env;
	if (!var)
		return (0);
	key = get_key(var);
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
			return (update_var(curr, key, var));
		curr = curr->next;
	}
	free(key);
	return (0);
}

int	update_var(t_env *curr, char *key, char *var)
{
	free(curr->value);
	curr->value = get_value(var);
	free(key);
	return (1);
}
