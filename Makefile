# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnayel <hnayel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/22 18:05:34 by hnayel            #+#    #+#              #
#    Updated: 2026/04/23 13:54:51 by hnayel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline -g3
INC = -Iinclude

SRC_DIR = src/
INIT_DIR = $(SRC_DIR)init/
LIBFT_DIR = $(SRC_DIR)libft/
BUILT_IN_DIR = $(SRC_DIR)built_in/
SIG_DIR = $(SRC_DIR)signals/
CLEAN_DIR = $(SRC_DIR)cleaning/
EXECUTOR_DIR = $(SRC_DIR)executor/
LEXER_DIR = $(SRC_DIR)lexer/
PARSER_DIR = $(SRC_DIR)parser/
OBJ_DIR = obj

SRC        = \
                $(SRC_DIR)main.c \
                $(INIT_DIR)init.c \
                $(SIG_DIR)signals.c \
                $(CLEAN_DIR)free.c \
                $(LIBFT_DIR)ft_mem.c \
                $(LIBFT_DIR)ft_str.c \
                $(LIBFT_DIR)ft_split.c \
                $(LIBFT_DIR)ft_char.c \
                $(LIBFT_DIR)ft_puts.c \
                $(LIBFT_DIR)ft_itoa.c \
                $(LEXER_DIR)lexer.c \
                $(LEXER_DIR)lexer_quotes.c \
                $(LEXER_DIR)lexer_redir.c \
                $(LEXER_DIR)lexer_utils.c \
                $(LEXER_DIR)lexer_word.c \
                $(PARSER_DIR)parser_cmd.c \
                $(PARSER_DIR)parser_utils.c \
                $(PARSER_DIR)parser.c \
                $(EXECUTOR_DIR)executor.c \
                $(EXECUTOR_DIR)executor_cmd.c \
                $(EXECUTOR_DIR)executor_pipe.c \
                $(EXECUTOR_DIR)executor_redir.c \
                $(BUILT_IN_DIR)builtins.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
