/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:16:09 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/26 14:25:54 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_var(t_env *curr, char *key, char *var)
{
	free(curr->value);
	curr->value = get_value(var);
	free(key);
	return (1);
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

void	var_doesnt_exist(char *var, t_input *input)
{
	if (!var)
		return ;
	add_back(&input->env, add_new(var));
}

int	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_export(t_ast *node, t_input *input)
{
	int		i;

	i = 1;
	if (!node->cmd->argv[1])
		return ;
	while (node->cmd->argv[i])
	{
		if (has_equal(node->cmd->argv[i]))
		{
			if (!var_already_exists(node->cmd->argv[i], input))
				var_doesnt_exist(node->cmd->argv[i], input);
		}
		i++;
	}
}
