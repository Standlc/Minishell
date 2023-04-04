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
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	child_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	exit(99);
}

void	child_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit\n", 2);
	exit(102);
}

void	backslash()
{
	ft_printf("\n");
}

void	backslash_quit(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	signal_for_wait(void)
{
	signal(SIGINT, backslash);
	//signal(SIGQUIT, backslash_quit);
}

int	child_signals()
{

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// if (signal(SIGINT, child_sigint) == SIG_ERR)
	// 	return (ft_putstr_fd("minishell: SIGINT error\n", 2), 1);
	// if (signal(SIGQUIT, child_sigquit) == SIG_ERR)
	// 	return (ft_putstr_fd("minishell: SIGQUIT error\n", 2), 1);
	return (0);
}