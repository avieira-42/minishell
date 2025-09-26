# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 17:55:52 by avieira-          #+#    #+#              #
#    Updated: 2025/09/26 16:18:52 by avieira-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL_SRCS = srcs/minishell.c

TTY_DRAWING_SRCS = srcs/tty_drawing/tty_drawing.c

PARSING_SRCS = srcs/parsing/parsing.c

ERROR_SRCS = srcs/error/error.c \
srcs/error/error_message.c

SRCS = $(MINISHELL_SRCS) \
$(TTY_DRAWING_SRCS) \
$(PARSING_SRCS) \
$(ERROR_SRCS)

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

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
	echo "Building $(NAME) executable"; \
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME); \

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@printf "Removing $(NAME) binaries... "
	@rm -rf $(OBJS)
	@echo "Done"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@printf "Removing executable... "
	@rm -rf $(NAME)
	@echo "Done"

re: fclean all
