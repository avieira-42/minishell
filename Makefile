# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 17:55:52 by avieira-          #+#    #+#              #
#    Updated: 2025/09/25 18:53:24 by avieira-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL_SRCS = srcs/minishell.c

BINARY_TREE_SRCS = srcs/binary_tree/main_binary_tree.c

TOKENIZER_SRCS = srcs/tokenizer/

SRCS = $(MINISHELL_SRCS)

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "Building executable"

%.o : %.c $(CC) $(CFLAGS)  -c $^ -o $@
	@echo "Compiling binaries"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "Compiling libft static library"

clean:
	@make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)
	@echo "Removing binaries"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo "Removing libft static library"
	rm -rf $(NAME)
	@echo "Removing executable"

re: fclean all
