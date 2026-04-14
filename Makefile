# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihi <jihi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 15:24:59 by jihi              #+#    #+#              #
#    Updated: 2026/04/14 12:56:24 by jihi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -Iinclude

SRC_DIR = src
INIT_DIR = $(SRC_DIR)/init
LIBFT_DIR = $(SRC_DIR)/libft
BUILT_IN_DIR = $(SRC_DIR)/built_in
OBJ_DIR = obj

SRC = \
	$(SRC_DIR)/main.c					\
	$(INIT_DIR)/init_shell.c			\
	$(INIT_DIR)/node_utils.c			\
	$(LIBFT_DIR)/ft_strcmp.c			\
	$(LIBFT_DIR)/ft_strdup.c			\
	$(LIBFT_DIR)/ft_strlen.c			\
	$(BUILT_IN_DIR)/get_built_in_type.c	\

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