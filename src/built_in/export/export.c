/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 12:16:09 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 14:19:22 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_error(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(str[0] >= 'a' && str[0] <= 'z')
		&& !(str[0] >= 'A' && str[0] <= 'Z')
		&& str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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

int	builtin_export(t_ast *node, t_input *input)
{
	int	i;
	int	status;

	i = 1;
	status = 1;
	if (!node->cmd->argv[1])
		return (0);
	while (node->cmd->argv[i])
	{
		if (!is_valid_identifier(node->cmd->argv[i]))
		{
			print_export_error(node->cmd->argv[i]);
			status = 1;
		}
		else if (has_equal(node->cmd->argv[i]))
		{
			if (!var_already_exists(node->cmd->argv[i], input))
				var_doesnt_exist(node->cmd->argv[i], input);
		}
		i++;
	}
	return (status);
}
