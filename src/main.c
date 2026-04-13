/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:19:29 by jihi              #+#    #+#             */
/*   Updated: 2026/04/13 20:24:38 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	(void)ac;
	(void)av;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	for (t_env *tmp = shell->env; tmp; tmp = tmp->next)
		printf("%s=%s\n", tmp->key, tmp->value);
	
	return (0);
}
