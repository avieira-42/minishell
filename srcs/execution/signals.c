#include "../minishell.h"

void	signal_prompt(int signal)
{
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_signal = signal + 128;
}

void	signal_heredoc(int signal)
{
	ft_putchar_fd('\n', 2);
	close(0);
	g_last_signal = signal + 128;
}

void	signal_broken_pipe(int signal)
{
	(void)signal;
	return ;
}

void	signal_prompt_setup(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_prompt);
}

void	signal_after_readline_setup(t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	if (g_last_signal == 130)
	{
		shell->exit_code = g_last_signal;
		g_last_signal = -1;
	}
}
