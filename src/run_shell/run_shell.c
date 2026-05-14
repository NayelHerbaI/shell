/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 17:24:22 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/14 16:19:42 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_prompt(t_input *input)
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
		return (1);
	}
	return (0);
}

void	process_line(t_input *input)
{
	int	heredoc_status;

	if (check_unclosed_quotes(input->linebuffer) != 0)
		input->exit_status = 2;
	else
	{
		input->tokens = lexer(input->linebuffer);
		if (check_syntax(input->tokens) != 0)
			input->exit_status = 2;
		else
		{
			expand_tokens(input->tokens, input);
			merge_joined_tokens(&input->tokens);
			input->ast = parser(input->tokens);
			heredoc_status = prepare_heredocs(input->ast);
			if (heredoc_status != 0)
				input->exit_status = heredoc_status;
			else
				input->exit_status = executor(input->ast, input);
			close_heredoc_fds(input->ast);
			free_ast(input->ast);
			input->ast = NULL;
		}
		ft_free_list(&input->tokens);
	}
}

void	run_shell(t_input *input)
{
	while (1)
	{
		if (read_prompt(input))
			break ;
		if (input->linebuffer && input->linebuffer[0] != '\0')
		{
			add_history(input->linebuffer);
			process_line(input);
		}
		ft_free_str(input->linebuffer);
		input->linebuffer = NULL;
	}
}
