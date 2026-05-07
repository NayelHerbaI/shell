/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:10:40 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 14:25:02 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_input *input, char *var)
{
	t_env	*curr;
	t_env	*prev;
	
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
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	builtin_unset(t_ast *node, t_input *input)
{
	int	i;

	i = 1;
	while (node->cmd->argv[i])
	{
		remove_env_var(input, node->cmd->argv[i]);
		i++;
	}
	return (0);
}



// int	builtin_unset(t_ast *node, t_input *input)
// {
// 	t_env	*curr;
// 	t_env	*prev;
// 	char	*var;

// 	if (!node->cmd->argv[1])
// 		return (0);
// 	var = node->cmd->argv[1];
// 	curr = input->env;
// 	prev = NULL;
// 	while (curr)
// 	{
// 		if (!ft_strcmp(curr->key, var))
// 		{
// 			if (prev)
// 				prev->next = curr->next;
// 			else
// 				input->env = curr->next;
// 			free(curr->key);
// 			free(curr->value);
// 			free(curr);
// 			return (0);
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	return (0);
// }
