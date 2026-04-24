/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:05:51 by hnayel            #+#    #+#             */
/*   Updated: 2026/04/24 15:46:31 by hnayel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_lexbuf	t_lexbuf;
typedef struct s_input	t_input;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_ast	t_ast;
typedef struct s_env	t_env;

extern int				g_signal;

enum				e_token_type
{
	INREDIR,
	OUTREDIR,
	PIPE,
	SPACE_,
	TAB_,
	OPERATOR,
	APPOUTREDIR,
	HEREDOC,
	WORD
};

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE
}	t_ast_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redirs;
}	t_cmd;

typedef struct s_ast
{
	t_ast_type		type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_utils
{
	int				i;
	int				j;
	int				start;
	int				varname_start;
	int				end;
	int				varname_len;
	int				varcontent_len;
	int				varcontent_start;
	int				env_index;
	char			*varname1;
	char			*varcontent1;
}	t_utils;

typedef struct s_input
{
	char			*linebuffer;
	t_lexbuf		*tokens;
	t_ast			*ast;
	size_t			nread;
	int				exit_status;
	t_env			*env;
	char			**env_copy;
	int				again;
	int				len;
}	t_input;

typedef struct s_lexbuf
{
	struct s_lexbuf	*next;
	struct s_lexbuf	*prev;
	char			*value;
	char			**env;
	int				type;
	t_input			*input;
}	t_lexbuf;

typedef struct s_env // Env pour unset et export.
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* PROGRAM */
int			main(int ac, char **av, char **env);

/* INIT */
void		init_utils(t_utils *utils);
void		init_struct(t_input *input, char **env);
void		reset_iterators(t_utils *utils);
t_env		*init_env(char **envp);
char		**init_env_copy(char **env);

/* NODE_UTILS */

void		add_back(t_env **list, t_env *new);
t_env		*add_new(char *str);

/* SIGNALS */
void		signal_readline(int signum);
void		signal_readline2(int signum);
void		signal_pipex(int signum);
void		signal_here_doc(int signum);

/* FREE */
void		ft_free_str(char *s);
void		ft_free_tab(char **tab);
void		ft_free_list(t_lexbuf **tokens);

/* LEXER */
t_lexbuf	*lexer(char *line);
int			lex_word(char *line, int i, t_lexbuf **tokens);
int			lex_squote(char *line, int i, t_lexbuf **tokens);
int			lex_dquote(char *line, int i, t_lexbuf **tokens);
int			lex_pipe(char *line, int i, t_lexbuf **tokens);
int			lex_redir(char *line, int i, t_lexbuf **tokens);
t_lexbuf	*add_token(t_lexbuf **tokens, char *value, int type);

/* PARSER */
t_ast		*parser(t_lexbuf *tokens);
t_ast		*parse_command(t_lexbuf **tok);
t_ast		*new_ast(t_ast_type type);
t_cmd		*new_cmd(void);
t_redir		*new_redir(t_redir_type type, char *file);
void		free_redir(t_redir *redir);
void		free_ast(t_ast *ast);

/* EXECUTOR */
void		executor(t_ast *ast, char **env);
void		exec_cmd(t_ast *node, char **env);
void		exec_pipe(t_ast *node, char **env);
void		exec_redirs(t_redir *redir);
char		*find_path(char *cmd, char **env);
int			is_builtin(char *cmd);
void		exec_builtin(t_ast *node, char **env);

/* BUILT_IN */
void		builtin_cd(t_ast *node, char **env);
void		builtin_unset(t_ast *node, char **env);

#endif
