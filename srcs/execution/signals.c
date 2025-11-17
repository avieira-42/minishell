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
