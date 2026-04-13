/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:48:45 by jihi              #+#    #+#             */
/*   Updated: 2026/04/13 20:04:25 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_FUNCTIONS_H
# define MS_FUNCTIONS_H

//				init_shell.c

t_shell	*init_shell(char **env);
t_env	*init_env(char **env);

//				node_utils.c

t_env	*add_new(char *str);
void	add_back(t_env **list, t_env *new);









// t_builtin	get_builtin_type(char *cmd_name);
// int			is_builtin(t_cmd *cmd);
// int			is_parent_builtin(t_cmd *cmd);

// t_msret		exec_command(t_shell *sh, t_cmd *cmd);
// t_msret		exec_single(t_shell *sh, t_cmd *cmd);
// t_msret		exec_pipeline(t_shell *sh, t_cmd *cmd);

// t_msret		apply_redirs(t_redir *redirs);
// t_msret		save_stdio(int saved[2]);
// t_msret		restore_stdio(int saved[2]);

// char		*resolve_cmd_path(t_shell *sh, char *cmd_name);
// int			msret_to_exit_status(t_msret ret);

#endif