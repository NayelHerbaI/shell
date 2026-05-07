/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:09:44 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 15:15:55 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input_end(t_input *input)
{
	if (!input)
		return ;
	if (input->ast)
	{
		free_ast(input->ast);
		input->ast = NULL;
	}
	if (input->tokens)
	{
		ft_free_list(&input->tokens);
		input->tokens = NULL;
	}
	if (input->linebuffer)
	{
		free(input->linebuffer);
		input->linebuffer = NULL;
	}
	if (input->env)
	{
		free_env_list(input->env);
		input->env = NULL;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

void	close_heredoc_fds(t_ast *node)
{
	t_redir	*redir;

	if (!node)
		return ;
	if (node->type == AST_PIPE)
	{
		close_heredoc_fds(node->left);
		close_heredoc_fds(node->right);
		return ;
	}
	if (node->type == AST_CMD && node->cmd)
	{
		redir = node->cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->heredoc_fd >= 0)
			{
				close(redir->heredoc_fd);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
	}
}
