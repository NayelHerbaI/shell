# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/22 18:05:34 by hnayel            #+#    #+#              #
#    Updated: 2026/05/09 19:02:57 by hnayel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
INC = -Iinclude

SRC_DIR = src/
INIT_DIR = $(SRC_DIR)init/
LIBFT_DIR = $(SRC_DIR)libft/
BUILT_IN_DIR = $(SRC_DIR)built_in/
SIG_DIR = $(SRC_DIR)signals/
CLEAN_DIR = $(SRC_DIR)cleaning/
EXECUTOR_DIR = $(SRC_DIR)executor/
EXECUTOR_CMD_DIR = $(EXECUTOR_DIR)executor_cmd/
EXECUTOR_PIPE_DIR = $(EXECUTOR_DIR)executor_pipe/
LEXER_DIR = $(SRC_DIR)lexer/
PARSER_DIR = $(SRC_DIR)parser/
RUN_SHELL_DIR = $(SRC_DIR)run_shell/
HEREDOC_DIR = $(EXECUTOR_DIR)heredoc/
CD_DIR = $(BUILT_IN_DIR)cd/
PWD_DIR = $(BUILT_IN_DIR)pwd/
UNSET_DIR = $(BUILT_IN_DIR)unset/
EXPORT_DIR = $(BUILT_IN_DIR)export/
ECHO_DIR = $(BUILT_IN_DIR)echo/
EXIT_DIR = $(BUILT_IN_DIR)exit/
ENV_DIR = $(BUILT_IN_DIR)env/
EXPANDER_DIR = $(LEXER_DIR)expander/
OBJ_DIR = obj/

SRC        = \
                $(SRC_DIR)main.c \
                $(INIT_DIR)init.c \
                $(INIT_DIR)init_env.c \
                $(INIT_DIR)node_utils.c \
                $(INIT_DIR)env_to_array.c \
                $(RUN_SHELL_DIR)run_shell.c \
                $(RUN_SHELL_DIR)check_syntax.c \
                $(SIG_DIR)signals.c \
                $(CLEAN_DIR)free.c \
                $(CLEAN_DIR)cleaning.c \
                $(LIBFT_DIR)ft_mem.c \
                $(LIBFT_DIR)ft_str.c \
                $(LIBFT_DIR)ft_split.c \
                $(LIBFT_DIR)ft_char.c \
                $(LIBFT_DIR)ft_puts.c \
                $(LIBFT_DIR)ft_itoa.c \
                $(LIBFT_DIR)ft_atoi.c \
                $(LEXER_DIR)lexer.c \
                $(LEXER_DIR)lexer_quotes.c \
                $(LEXER_DIR)lexer_redir.c \
                $(LEXER_DIR)lexer_utils.c \
                $(LEXER_DIR)lexer_word.c \
				$(EXPANDER_DIR)expander.c	\
				$(EXPANDER_DIR)expander_utils.c	\
                $(PARSER_DIR)parser_cmd.c \
                $(PARSER_DIR)parser_utils.c \
                $(PARSER_DIR)parser.c \
                $(EXECUTOR_DIR)executor.c \
                $(EXECUTOR_CMD_DIR)executor_cmd.c \
                $(EXECUTOR_CMD_DIR)executor_path.c \
                $(EXECUTOR_CMD_DIR)executor_status.c \
                $(EXECUTOR_CMD_DIR)executor_execve_error.c \
                $(EXECUTOR_PIPE_DIR)executor_pipe.c \
                $(EXECUTOR_PIPE_DIR)error_handling.c \
                $(EXECUTOR_DIR)executor_redir.c \
                $(HEREDOC_DIR)heredoc.c \
                $(HEREDOC_DIR)executor_heredoc.c \
                $(BUILT_IN_DIR)builtins.c \
                $(BUILT_IN_DIR)builtin_exit_utils.c \
                $(BUILT_IN_DIR)builtins_helpers.c \
                $(CD_DIR)cd.c \
                $(UNSET_DIR)unset.c \
                $(EXPORT_DIR)export.c \
                $(EXPORT_DIR)var_utils.c \
                $(ECHO_DIR)echo.c \
                $(PWD_DIR)pwd.c \
                $(ENV_DIR)env.c \
                $(EXIT_DIR)exit.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
