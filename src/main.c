/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:27:45 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 19:21:00 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	check_unclosed_quotes(char *line)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (quote == 0 && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote != 0 && line[i] == quote)
			quote = 0;
		i++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("syntax error: unclosed quote\n", STDERR_FILENO);
		return (2);
	}
	return (0);
}

static int	is_redir_token(int type)
{
	if (type == INREDIR || type == OUTREDIR
		|| type == APPOUTREDIR || type == HEREDOC)
		return (1);
	return (0);
}

int	check_syntax(t_lexbuf *tokens)
{
	t_lexbuf	*curr;

	if (!tokens)
		return (0);
	if (tokens->type == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (2);
	}
	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (!curr->next || curr->next->type == PIPE)
			{
				ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
				return (2);
			}
		}
		else if (is_redir_token(curr->type))
		{
			if (!curr->next || curr->next->type != WORD)
			{
				ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
				return (2);
			}
		}
		curr = curr->next;
	}
	return (0);
}

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