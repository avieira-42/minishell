NAME = minishell

CC = cc
ADD_FLAGS=
CFLAGS = -g -Wall -Wextra -Werror $(ADD_FLAGS)
FLAG_READLINE = -lreadline
LDFLAGS = -I/usr/local/opt/readline/include -L/usr/local/op/readline/lib

LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MINISHELL_SRCS = srcs/minishell.c

BINARY_TREE_SRCS = srcs/binary_tree/binary_tree.c \
				   srcs/binary_tree/binary_tree_error.c \
				   srcs/binary_tree/command.c \
				   srcs/binary_tree/redirects.c \
				   srcs/binary_tree/binary_tree_clear.c

TTY_DRAWING_SRCS = srcs/tty_drawing/tty_drawing.c

PARSING_SRCS = srcs/parsing/tokenizer.c \
				srcs/parsing/token_list.c \
				srcs/parsing/quotation.c \
				srcs/parsing/expand.c \
				srcs/parsing/environment_variables.c \
				srcs/parsing/token_identify.c \
				srcs/parsing/user_input_parse.c \
				srcs/parsing/token_error.c \

ERROR_SRCS = srcs/error/error.c \
			 srcs/error/error_message.c

BUILTINS_SRCS = srcs/builtins/builtins_echo.c \
				srcs/builtins/builtins_exec.c \
				srcs/builtins/builtins_exit.c \
				srcs/builtins/builtins_pwd.c \
				srcs/builtins/builtins_env.c

EXECUTION_SRCS = srcs/execution/program_path_find.c \
				 srcs/execution/command_execute.c \
				 srcs/execution/process_control.c \
				 srcs/execution/heredoc.c \
				 srcs/execution/execution_utils.c

CLEANING_SRCS = srcs/cleaning/program_clean.c
				
SRCS = $(MINISHELL_SRCS) \
		$(TTY_DRAWING_SRCS) \
		$(ERROR_SRCS) \
		$(BUILTINS_SRCS) \
		$(EXECUTION_SRCS) \
		$(CLEANING_SRCS) \
		$(PARSING_SRCS) \
		$(BINARY_TREE_SRCS)


OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

%.o: %.c
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

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "Building $(NAME) executable"; \
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(FLAG_READLINE); \

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

clean:
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@printf "Removing $(NAME) binaries... "
	@rm -rf $(OBJS)
	@echo "Done"

fclean: clean
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@printf "Removing executable... "
	@rm -rf $(NAME)
	@echo "Done"

re: fclean all
