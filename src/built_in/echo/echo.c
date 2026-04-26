/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:52:55 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/26 15:04:36 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_expansion(char *var, t_input *input)
{
	t_env	*curr;

	curr = input->env;
	while (curr)
	{
		if (ft_strlen(var) > 1 && !ft_strcmp(curr->key, &var[1]))
			ft_putstr_fd(curr->value, STDOUT_FILENO);
		curr = curr->next;
	}
}

int	is_var_expansion(char *var)
{
	if (var[0] == '$' && var[1])
		return (1);
	return (0);
}

void	builtin_echo(t_ast *node, t_input *input)
{
	int	i;
	int	newline;

	(void)input;
	i = 1;
	newline = 1;
	if (node->cmd->argv[1] && !ft_strncmp(node->cmd->argv[1], "-n", 3))
	{
		newline = 0;
		i = 2;
	}
	while (node->cmd->argv[i])
	{
		if (is_var_expansion(node->cmd->argv[i]))
		{
			var_expansion(node->cmd->argv[i], input);
			if (node->cmd->argv[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd(node->cmd->argv[i], STDOUT_FILENO);
			if (node->cmd->argv[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
