#include "minishell.h"

void	handle_sigint(int sig)
{
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
	// sigaction(SIGINT, sact, (void *)data);
	// sigaction(SIGQUIT, sact, (void *)data);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	get_line(t_data *data)
{
	char	*line;

	line = readline(PROMPT);
	while (line)
	{
		if (*line)
			add_history(line);
		parse_line(data, line);
		free_data(data);
		free(line);
		line = readline(PROMPT);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	hook_signals();
	get_line(&data);
	printf("Exit\n");
	rl_clear_history();
	return (0);
}
