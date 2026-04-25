/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:28:46 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/24 15:56:43 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_input *input, char **env)
{
	input->linebuffer = NULL;
	input->tokens = NULL;
	input->env = NULL;
	input->ast = NULL;
	input->nread = 0;
	input->exit_status = 0;
	input->again = 0;
	input->len = 0;
	input->env_copy = init_env_copy(env);
	input->env = init_env(env);
}

void	init_utils(t_utils *utils)
{
	utils->i = 0;
	utils->j = 0;
	utils->start = 0;
	utils->varname_start = 0;
	utils->end = 0;
	utils->varname_len = 0;
	utils->varcontent_len = 0;
	utils->varcontent_start = 0;
	utils->env_index = 0;
	utils->varname1 = NULL;
	utils->varcontent1 = NULL;
}

void	reset_iterators(t_utils *utils)
{
	utils->i = 0;
	utils->j = 0;
	utils->start = 0;
	utils->end = 0;
}
