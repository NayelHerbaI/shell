/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:33:51 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:01:29 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_redirs(t_redir *redir)
{
	while (redir)
	{
		if (apply_redir(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
