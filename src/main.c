/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:45 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 15:37:40 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	run_shell(t_input *input)
{
	int	heredoc_status;

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
			expand_tokens(input->tokens, input);
			input->ast = parser(input->tokens);
			heredoc_status = prepare_heredocs(input->ast);
			if (heredoc_status != 0)
				input->exit_status = heredoc_status;
			else
				input->exit_status = executor(input->ast, input);
			close_heredoc_fds(input->ast);
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