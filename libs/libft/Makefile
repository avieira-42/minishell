# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 12:18:39 by avieira-          #+#    #+#              #
#    Updated: 2025/10/03 18:30:12 by avieira-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = srcs/ft_atoi.c srcs/ft_bzero.c srcs/ft_isalnum.c srcs/ft_isalpha.c
SRCS += srcs/ft_isascii.c srcs/ft_isdigit.c srcs/ft_isspace.c
SRCS += srcs/ft_isprint.c srcs/ft_memcpy.c srcs/ft_memset.c srcs/ft_strlen.c
SRCS += srcs/ft_tolower.c srcs/ft_memmove.c srcs/ft_strnstr.c srcs/ft_strchr.c
SRCS += srcs/ft_strrchr.c srcs/ft_strtrim.c srcs/ft_split.c srcs/ft_putendl_fd.c
SRCS += srcs/ft_strlcat.c srcs/ft_itoa.c srcs/ft_strdup.c srcs/ft_strncmp.c
SRCS += srcs/ft_memcmp.c srcs/ft_calloc.c srcs/ft_substr.c srcs/ft_strjoin.c
SRCS += srcs/ft_strmapi.c srcs/ft_striteri.c srcs/ft_putchar_fd.c 
SRCS += srcs/ft_putstr_fd.c srcs/ft_toupper.c srcs/ft_strlcpy.c srcs/ft_memchr.c
SRCS += srcs/ft_putnbr_fd.c srcs/ft_printf.c srcs/ft_printadd.c
SRCS += srcs/ft_printchar.c srcs/ft_printhex.c srcs/ft_printnbr.c
SRCS += srcs/ft_printunsign_nbr.c srcs/ft_printstr.c srcs/ft_issign.c
SRCS += srcs/ft_free_matrix.c srcs/i_merge_sort.c srcs/ft_atol.c
SRCS += srcs/ft_lstnew_bonus.c srcs/ft_lstdelone_bonus.c srcs/ft_strcmp.c
SRCS += srcs/ft_lstsize_bonus.c srcs/ft_lstlast_bonus.c srcs/ft_dblylst_clear.c
SRCS += srcs/ft_lstadd_back_bonus.c srcs/ft_lstadd_front_bonus.c
SRCS += srcs/ft_lstclear_bonus.c srcs/ft_lstiter_bonus.c srcs/ft_lstmap_bonus.c
SRCS += srcs/ft_dblylst_new.c srcs/ft_dblylst_addback.c srcs/ft_dblylst_last.c 
SRCS += srcs/ft_dblylst_size.c srcs/ft_is_int.c srcs/ft_bool_strcmp.c
SRCS += srcs/get_next_line.c srcs/get_next_line_utils.c
SRCS += srcs/ft_printadd_fd.c srcs/ft_printf_fd.c srcs/ft_printchar_fd.c
SRCS += srcs/ft_printstr_fd.c srcs/ft_printnbr_fd.c srcs/ft_printunsign_nbr_fd.c
SRCS += srcs/ft_printhex_fd.c srcs/ft_bool_strncmp.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Build library with live progress bar
$(NAME):
	@total=$(words $(SRCS)); \
	current=0; \
	bar_length=30; \
	for f in $(SRCS); do \
		current=$$((current+1)); \
		percent=$$((current*100/total)); \
		filled=$$((bar_length*current/total)); \
		empty=$$((bar_length-filled)); \
		bar="$$(printf '%0.s#' $$(seq 1 $$filled))$$(printf '%0.s-' $$(seq 1 $$empty))"; \
		printf "Compiling libft binaries [%s] %3d%% \r" "$$bar" $$percent; \
		cc $(CFLAGS) -c $$f -o $${f%.c}.o; \
	done; \
	echo ""; \
	ar rcs $(NAME) $(OBJS); \

# Clean object files
clean:
	@printf "Removing libft binaries... "
	@rm -f $(OBJS)
	@echo "Done"

# Clean objects and library
fclean: clean
	@printf "Removing libft executable... "
	@rm -f $(NAME)
	@echo "Done"

# Rebuild everything
re: fclean all
