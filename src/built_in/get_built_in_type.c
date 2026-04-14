/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_built_in_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 12:51:01 by jihi              #+#    #+#             */
/*   Updated: 2026/04/14 13:06:11 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	return (get_builtin_type(cmd->argv[0]) != BI_NONE);
}

t_builtin	get_builtin_type(char *cmd_name)
{
	if (!cmd_name)
		return (BI_NONE);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (BI_ECHO);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (BI_CD);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (BI_PWD);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (BI_EXPORT);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (BI_UNSET);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (BI_ENV);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (BI_EXIT);
	return (BI_NONE);
}