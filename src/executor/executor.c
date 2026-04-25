/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:52 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/25 17:50:02 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_ast *node, t_input *input)
{
	if (!node)
		return ;
	if (node->type == AST_PIPE)
		exec_pipe(node, input);
	else if (node->type == AST_CMD)
	{
		if (node->cmd && node->cmd->argv && node->cmd->argv[0])
		{
			if (is_builtin(node->cmd->argv[0]))
				exec_builtin(node, input);
			else
				exec_cmd(node, input);
		}
	}
}
