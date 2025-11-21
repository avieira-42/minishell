/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:38:39 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/21 18:02:12 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"
#include <readline/readline.h>
#include <unistd.h>
#include "types.h"

int	g_last_signal;

int	preprocess_input(t_shell *shell)
{
	add_history(shell->user_input);
	if (user_input_parse(shell) == -1)
	{
		shell->exit_code = 2;
		ft_token_lst_clear(&shell->tokens);
	}
	else
		token_lst_clear_safe(&shell->tokens);
	return (shell->tree != NULL);
}

static
void	minishell_loop(t_shell *shell)
{
	while (TRUE)
	{
		signal_prompt_setup();
		shell->user_input = readline(GREEN "minishell" COLOR_RESET "$> " RESET);
		signal_after_readline_setup(shell);
		if (shell->user_input == NULL)
			break ;
		if (preprocess_input(shell) == 0)
			continue ;
		if (handle_heredoc(shell) == 0)
			continue ;
		tree_execute(shell);
		iteration_clear(shell);
	}
	rl_clear_history();
	ft_free_matrix(shell->env_vars);
	ft_free_matrix(shell->export_vars.m_array);
	close_all_fds(3, shell->highest_fd);
}

void	minishell_init(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->lvl_message = false;
	shell->argc = argc;
	shell->argv = argv;
	shell->envp = envp;
	shell->user_input = NULL;
	shell->exit_code = 0;
	shell->merge_ret = 0;
	shell->export_vars.m_array = NULL;
	shell->env_vars = NULL;
	shell->tokens = NULL;
	shell->tree = NULL;
	shell->highest_fd = 2;
	shell->env_size = minishell_envp_size(shell);
	shell->env_vars = minishell_env_dup(shell, NULL);
	shell->export_vars.length = shell->env_size;
	shell->export_vars.m_array = minishell_env_dup(shell, NULL);
	str_merge_sort(shell->export_vars, &shell->merge_ret);
	if (shell->merge_ret == -1)
		exit_clean(shell, 66, NULL, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 1)
	{
		ft_printf_fd(2, "Error: minishell: Usage: ./minishell");
		return (1);
	}
	minishell_init(&shell, argc, argv, envp);
	minishell_loop(&shell);
}
