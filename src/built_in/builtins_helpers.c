/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:10:00 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 18:13:54 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin < 0 || *saved_stdout < 0)
	{
		if (*saved_stdin >= 0)
			close(*saved_stdin);
		if (*saved_stdout >= 0)
			close(*saved_stdout);
		return (1);
	}
	return (0);
}

int	handle_exit_builtin(t_ast *node, t_input *input,
	int saved_stdin, int saved_stdout)
{
	int	status;

	if (exit_will_return(node))
	{
		status = builtin_exit(node, input);
		restore_fds(saved_stdin, saved_stdout);
		return (status);
	}
	restore_fds(saved_stdin, saved_stdout);
	return (builtin_exit(node, input));
}
