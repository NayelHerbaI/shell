/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:05:51 by hnayel            #+#    #+#             */
/*   Updated: 2026/05/09 20:25:12 by hnayel           ###   ########.fr       */
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

# define QUOTE_NONE 0
# define QUOTE_SINGLE 1
# define QUOTE_DOUBLE 2
# define PROTECTED_DOLLAR 1
# define SYNTAX_ERROR_PIPE "syntax error near unexpected token `|'\n"
# define SYNTAX_ERROR_NEWLINE "syntax error near unexpected token `newline'\n"
# define COMMAND_NOT_FOUND ": command not found\n"
# define QUIT_CORE_DUMPED "Quit (core dumped)\n"

typedef struct s_lexbuf	t_lexbuf;
typedef struct s_input	t_input;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_ast	t_ast;
typedef struct s_env	t_env;

extern volatile sig_atomic_t	g_signal;

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
	int				heredoc_fd;
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
	int				quote_type;
	int				join_next;
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
char		**env_to_array(t_env *env);
char		*get_key(char *str);
char		*get_value(char *str);

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
void		free_env_array(char **envp);
void		free_input_end(t_input *input);
void		free_env_list(t_env *env);
void		close_heredoc_fds(t_ast *node);

/* LEXER */
t_lexbuf	*lexer(char *line);
int			lex_word(char *line, int i, t_lexbuf **tokens);
int			lex_squote(char *line, int i, t_lexbuf **tokens);
int			lex_dquote(char *line, int i, t_lexbuf **tokens);
int			lex_pipe(char *line, int i, t_lexbuf **tokens);
int			lex_redir(char *line, int i, t_lexbuf **tokens);
t_lexbuf	*add_token(t_lexbuf **tokens, char *value, int type);
void		expand_tokens(t_lexbuf *tokens, t_input *input);
void		set_last_quote_type(t_lexbuf *tokens, int quote_type);
int			is_word_join_char(char c);
void		set_last_join_next(t_lexbuf *tokens, int join_next);
void		merge_joined_tokens(t_lexbuf **tokens);
int			check_unclosed_quotes(char *line);
char		*join_and_free(char *s1, char *s2);
char		*expand_exit_value(char *value, t_input *input, int *i);
char		*expand_env_var(char *word, char *result, t_input *input, int *i);
int			is_var_char(char c);

/* PARSER */
t_ast		*parser(t_lexbuf *tokens);
t_ast		*parse_command(t_lexbuf **tok);
t_ast		*new_ast(t_ast_type type);
t_cmd		*new_cmd(void);
t_redir		*new_redir(t_redir_type type, char *file);
void		free_redir(t_redir *redir);
void		free_ast(t_ast *ast);
int			count_args(t_lexbuf *tok);

/* EXECUTOR */
int			executor(t_ast *ast, t_input *input);
int			exec_cmd(t_ast *node, t_input *input);
int			exec_pipe(t_ast *node, t_input *input);
int			exec_redirs(t_redir *redir);
char		*find_path(char *cmd, char **env);
int			is_builtin(char *cmd);
int			exec_builtin(t_ast *node, t_input *input);
int			status_from_wait(int status);
int			prepare_heredocs(t_ast *node);
int			apply_heredoc(t_redir *redir);
void		print_signal_message(int status);
int			status_from_wait(int status);
char		*find_path(char *cmd, char **env);
int			status_from_wait(int status);
void		print_signal_message(int status);
void		exit_execve_error(char *cmd, char *path, char **env);
void 		print_command_not_found(char *cmd, char **env);
void		setup_pipe_child_signals(void);
int			close_pipe_error(int fd[2]);
void		exec_left_pipe_child(t_ast *node, t_input *input, int fd[2]);
void		exec_right_pipe_child(t_ast *node, t_input *input, int fd[2]);
int			apply_redir(t_redir *redir);
void		restore_heredoc_stdin(int saved_stdin);
int			prepare_cmd_heredocs(t_ast *node);
int			prepare_heredocs(t_ast *node);
int			read_one_heredoc(t_redir *redir);
void		write_heredoc_line(char *line, int fd);
int			apply_heredoc(t_redir *redir);

/* BUILT_IN */
int			builtin_cd(t_ast *node);
int			builtin_unset(t_ast *node, t_input *input);
int			builtin_export(t_ast *node, t_input *input);
int			builtin_echo(t_ast *node, t_input *input);
int			builtin_exit(t_ast *node, t_input *input);
int			builtin_pwd(void);
int			builtin_env(t_input *input);
int			exit_will_return(t_ast *node);
int			is_numeric_arg_for_exit(char *str);
int			handle_exit_builtin(t_ast *node, t_input *input, int saved_stdin, int saved_stdout);
int			save_fds(int *saved_stdin, int *saved_stdout);
int			restore_fds(int saved_stdin, int saved_stdout);
int			var_already_exists(char *var, t_input *input);
int			update_var(t_env *curr, char *key, char *var);
void		var_doesnt_exist(char *var, t_input *input);

/* RUN_SHELL */
void		run_shell(t_input *input);
int			check_syntax(t_lexbuf *tokens);
int			is_redir_token(int type);
int			check_unclosed_quotes(char *line);

#endif
