/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:10:40 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/25 17:51:51 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_ast *node, t_input *input)
{
	int		i;
	int		var_len;
	char	*var;

	i = 0;
	if (!node->cmd->argv[1])
		return ;
	var = node->cmd->argv[1];
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], var_len) && env[i][var_len] == '=')
		{
				free(env[i]);
				while (env[i + 1])
				{
					env[i] = env[i + 1];
					i++;
				}
				env[i] = NULL;
				return ;
		}
		i++;
	}
}
