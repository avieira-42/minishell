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
				   srcs/binary_tree/binary_tree_clear.c \
				   srcs/binary_tree/command.c \
				   srcs/binary_tree/command_clear.c \
				   srcs/binary_tree/redirect.c \
				   srcs/binary_tree/redirect_clear.c

PARSING_SRCS = srcs/parsing/tokenizer.c \
				srcs/parsing/token_list.c \
				srcs/parsing/tokenizer_utils.c \
				srcs/parsing/quotation.c \
				srcs/parsing/expand.c \
				srcs/parsing/expand_utils.c \
				srcs/parsing/environment_variables.c \
				srcs/parsing/environment_variables_utils.c \
				srcs/parsing/token_identify.c \
				srcs/parsing/user_input_parse.c \

BUILTINS_SRCS = srcs/builtins/builtins_echo.c \
				srcs/builtins/builtins_exec.c \
				srcs/builtins/builtins_exit.c \
				srcs/builtins/builtins_pwd.c \
				srcs/builtins/builtins_cd.c \
				srcs/builtins/builtins_env.c \
				srcs/builtins/builtins_export.c \
				srcs/builtins/builtins_export_utils.c \
				srcs/builtins/builtins_export_plus_equal_handle.c \
				srcs/builtins/builtins_unset.c \
				srcs/builtins/builtins_logo.c \
				srcs/builtins/builtins_authors.c

EXECUTION_SRCS = srcs/execution/program_path_find.c \
				 srcs/execution/tree_execute.c \
				 srcs/execution/tree_execute_utils.c \
				 srcs/execution/process_control.c \
				 srcs/execution/heredoc.c \
				 srcs/execution/execution_utils.c \
				 srcs/execution/execution.c \
				 srcs/execution/signals.c

CLEANING_SRCS = srcs/cleaning/program_clean.c \
				srcs/cleaning/exit_clean.c \
				srcs/cleaning/cleaning.c
				
SRCS = $(MINISHELL_SRCS) \
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

valgrind: $(NAME)
	valgrind --suppressions=readline.supp --show-leak-kinds=all --leak-check=full --trace-children=yes --track-fds=yes ./$(NAME)

fdvalgrind: $(NAME)
	valgrind --suppressions=readline.supp --trace-children=yes --track-fds=yes ./$(NAME)
