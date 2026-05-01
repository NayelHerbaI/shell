/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:52 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/01 14:26:58 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_ast *node, t_input *input)
{
	if (!node)
		return (0);
	if (node->type == AST_PIPE)
		return (exec_pipe(node, input));
	if (node->type == AST_CMD)
	{
		if (node->cmd && node->cmd->argv && node->cmd->argv[0])
		{
			if (is_builtin(node->cmd->argv[0]))
				return (exec_builtin(node, input));
			return (exec_cmd(node, input));
		}
	}
	return (0);
}