/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:53 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/23 13:31:48 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str(char *s)
{
	if (s)
		free(s);
}

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_free_list(t_lexbuf **tokens)
{
	t_lexbuf	*tmp;
	t_lexbuf	*next;

	if (!tokens || !*tokens)
		return ;
	tmp = *tokens;
	while (tmp)
	{
		next = tmp->next;
		ft_free_str(tmp->value);
		free(tmp);
		tmp = next;
	}
	*tokens = NULL;
}
