/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:47:44 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/14 12:52:24 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *str)
{
	size_t	len;
	int		i;
	char	*new_string;

	i = 0;
	len = ft_strlen(str);
	new_string = malloc(sizeof(char) * len + 1);
	if (!new_string)
		return (NULL);
	while (str[i])
	{
		new_string[i] = str[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
