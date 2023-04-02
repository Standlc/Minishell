#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	hook_signals(void)
{
	// sigemptyset(&(sact->sa_mask));
	// sact->sa_flags = SA_SIGINFO | SA_RESTART;
	// sact->sa_sigaction = handle_signals;
	// sigaction(SIGINT, sact, (void *)pipelines);
	// sigaction(SIGQUIT, sact, (void *)pipelines);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	child_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
}

void	child_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit\n", 2);
}

int	child_signals()
{
	if (signal(SIGINT, child_sigint) == SIG_ERR)
		return (ft_putstr_fd("minishell: SIGINT error\n", 2), 1);
	if (signal(SIGQUIT, child_sigquit) == SIG_ERR)
		return (ft_putstr_fd("minishell: SIGQUIT error\n", 2), 1);
	return (0);
}