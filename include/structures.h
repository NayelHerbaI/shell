/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:22:04 by jihi              #+#    #+#             */
/*   Updated: 2026/04/13 16:15:32 by jihi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_msret		// Représente ce que tes fonctions C se disent entre elles.
{
	MS_OK = 0,
	MS_ERR,
	MS_MALLOC,
	MS_FORK,
	MS_PIPE,
	MS_DUP,
	MS_OPEN,
	MS_CLOSE,
	MS_EXECVE,
	MS_CMD_NOT_FOUND,
	MS_PERMISSION,
	MS_IS_DIR,
	MS_INVALID_ARG,
	MS_SYNTAX
}	t_msret;

typedef enum e_builtin		// Work in progress
{
	BI_NONE = 0,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}	t_builtin;

typedef enum e_redir_type	// Work in progress
{
	R_IN = 0,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir		// Représente un branchement d’entrée/sortie pour une commande.
{
	t_redir_type		type;
	char				*target;
	int					heredoc_fd;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd		// Représente une commande exécutable.
{
	char			**argv;
	t_builtin		builtin;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env		// Environnement sous forme de liste chainees assemblee de nouveau en char ** pour unset et export.
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell		// Représente l’état persistant du shell entre les commandes.
{
	t_env	*env;
	int		last_status;
}	t_shell;

#endif