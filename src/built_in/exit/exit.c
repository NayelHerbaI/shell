/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:26:55 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 14:31:30 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_arg(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit_numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

int	builtin_exit(t_ast *node, t_input *input)
{
	int	status;

	status = input->exit_status;
	if (!node->cmd->argv[1])
		exit(status);
	if (!is_numeric_arg(node->cmd->argv[1]))
	{
		print_exit_numeric_error(node->cmd->argv[1]);
		exit(2);
	}
	if (node->cmd->argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	status = ft_atoi(node->cmd->argv[1]);
	exit((unsigned char)status);
	return (status);
}
