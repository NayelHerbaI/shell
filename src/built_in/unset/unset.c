/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:10:40 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/01 15:40:01 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_ast *node, t_input *input)
{
	t_env	*curr;
	t_env	*prev;
	char	*var;

	if (!node->cmd->argv[1])
		return (0);
	var = node->cmd->argv[1];
	curr = input->env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->key, var))
		{
			if (prev)
				prev->next = curr->next;
			else
				input->env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
