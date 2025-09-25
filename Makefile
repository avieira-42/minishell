# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 17:55:52 by avieira-          #+#    #+#              #
#    Updated: 2025/09/25 23:32:57 by avieira-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL_SRCS = srcs/minishell.c

SRCS = $(MINISHELL_SRCS)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

# Default target
all: $(LIBFT) $(NAME)

# Build libft first
$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "Compiling libft static library"

# Build minishell with progress bar
$(NAME): $(LIBFT)
	@total=$(words $(SRCS)); \
	current=0; \
	bar_length=30; \
	for f in $(SRCS); do \
		current=$$((current+1)); \
		percent=$$((current*100/total)); \
		filled=$$((bar_length*current/total)); \
		empty=$$((bar_length-filled)); \
		bar="$$(printf '%0.s#' $$(seq 1 $$filled))$$(printf '%0.s-' $$(seq 1 $$empty))"; \
		printf "Compiling minishell binaries [%s] %3d%%\r" "$$bar" $$percent; \
		$(CC) $(CFLAGS) -c $$f -o $${f%.c}.o; \
	done; \
	echo ""; \
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME); \
	echo "Building executable"

# Clean object files
clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJS)
	@echo "Removing binaries"

# Clean objects and executable
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo "Removing libft static library"
	@rm -rf $(NAME)
	@echo "Removing executable"

# Rebuild everything
re: fclean all
