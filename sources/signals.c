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
	// signal(SIGUSR1, truc);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
