/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:45 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/24 15:57:55 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static void	run_shell(t_input *input)
{
	while (1)
	{
		signal(SIGINT, signal_readline);
		signal(SIGQUIT, SIG_IGN);
		input->linebuffer = readline("$> ");
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
			executor(input->ast, input->env_copy);
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
	init_struct(&input, env);
	run_shell(&input);
	return (input.exit_status);
}
