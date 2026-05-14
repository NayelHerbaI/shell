/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:45 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/14 14:51:06 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_input	input;
	int		status;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	init_struct(&input, env);
	run_shell(&input);
	status = input.exit_status;
	free_input_end(&input);
	return (status);
}
