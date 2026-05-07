/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 15:37:47 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/07 15:33:32 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_heredoc(t_redir *redir)
{
	if (redir->heredoc_fd < 0)
		return (1);
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
		return (1);
	close(redir->heredoc_fd);
	redir->heredoc_fd = -1;
	return (0);
}
