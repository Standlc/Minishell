#include "minishell.h"

void	display_data(t_data *data)
{
	int	i = 0;
	printf("[\n");
	while (data->commands[i].name)
	{
		printf("	{\n");
		printf("		name: %s,\n", data->commands[i].name);
		int	h = 0;
		printf("		options: [");
		while (data->commands[i].options[h])
		{
			printf("%s, ", data->commands[i].options[h]);
			h++;
		}
		printf("\b],\n");
		h = 0;
		printf("		arguments: [");
		while (data->commands[i].arguments[h])
		{
			printf("%s, ", data->commands[i].arguments[h]);
			h++;
		}
		printf("\b],\n");
		printf("		opertor: %d\n", data->commands[i].operator);
		printf("	},\n");
		i++;
	}
	printf("\n]\n");
}

void	handle_sigint(int sig)
{
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	// ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", 1);
	// ft_putstr_fd("\n", 2);
}

void	handle_sigquit(int sig)
{
	// printf("quit\n");
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
		// display_data(&data); 
		free_data(data);
		free(line);
		line = readline(PROMPT);
	}
	printf("end\n");
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	hook_signals();
	get_line(&data);
	// rl_clear_history();
	return (0);
}
