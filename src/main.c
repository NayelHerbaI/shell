/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:45 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/03 14:15:48 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	run_shell(t_input *input)
{
	while (1)
	{
		signal(SIGINT, signal_readline);
		signal(SIGQUIT, SIG_IGN);
		input->linebuffer = readline("$> ");
		if (g_signal == SIGINT)
		{
			input->exit_status = 130;
			g_signal = 0;
		}
		if (!input->linebuffer)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (input->linebuffer && input->linebuffer[0] != '\0')
		{
			add_history(input->linebuffer);
			input->tokens = lexer(input->linebuffer);
			input->ast = parser(input->tokens);
			if (prepare_heredocs(input->ast) != 0)
				input->exit_status = 1;
			else
				input->exit_status = executor(input->ast, input);
			free_ast(input->ast);
			input->ast = NULL;
			ft_free_list(&input->tokens);
		}
		ft_free_str(input->linebuffer);
		input->linebuffer = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_input	input;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	init_struct(&input, env);
	run_shell(&input);
	return (input.exit_status);
}
