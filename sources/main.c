#include "minishell.h"

int	g_status;

void	show_data(t_pipeline *pipelines)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	while (pipelines[i].commands)
	{
		printf("[\n");
		j = 0;
		while (pipelines[i].commands[j].is_end)
		{
			printf("\t{\n");
			if (pipelines[i].commands[j].arguments)
				printf("\t\tname: %s\n", pipelines[i].commands[j].arguments[0]);
			k = 1;
			printf("\t\targuments: [");
			while (pipelines[i].commands[j].arguments && pipelines[i].commands[j].arguments[k])
			{
				printf("%s, ", pipelines[i].commands[j].arguments[k]);
				k++;
			}
			printf("]\n");
			printf("\t\tinput: %d\n", pipelines[i].commands[j].input_file);
			printf("\t\touput: %d\n", pipelines[i].commands[j].output_file);
			printf("\t\tis_end: %d\n", pipelines[i].commands[j].is_end);
			printf("\t}\n");
			j++;
		}
		printf("\tparenthesis: %d\n", pipelines[i].parenthesis);
		printf("\toperator: %d\n", pipelines[i].operator);
		printf("]\n");
		i++;
	}
}

char	***environnement(char **new_env)
{
	static char	**env = NULL;

	if (new_env)
		env = new_env;
	return (&env);
}

char	*readline_handler(void)
{
	char	*prompt;
	char	*line;

	if (g_status)
		prompt = PROMPT_ERROR;
	else
		prompt = PROMPT;
	line = readline(prompt);
	return (line);
}

int	get_line(t_pipeline *pipelines, char **env)
{
	t_heredoc_fds	*heredoc_fds;
	char			*line;
	char			**new_env;

	line = readline_handler();
	new_env = duplicate_bigarray(env);
	if (g_status != 0)
		(free(line), exit(g_status));
	(void)environnement(new_env);
	while (line)
	{
		if (*line)
			add_history(line);
		if (!check_syntax(line))
		{
			heredoc_fds = handle_heredocs(line, heredoc_fds);
			if (!heredoc_fds)
			{
				free(line);
				break ;
			}
			pipelines = parse_line(line, heredoc_fds);
			close_heredoc_fds(heredoc_fds);
			free(heredoc_fds);
			free(line);
			if (pipelines)
			{
				// show_data(pipelines);
				execution_global(pipelines);
				free_pipelines(pipelines);
			}
		}
		line = readline_handler();
	}
	new_env = *(environnement(NULL));
	free_str_arr(new_env);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipeline	*pipelines;

	(void)argc;
	(void)argv;
	pipelines = NULL;
	// if (!isatty(0) || !isatty(1) || !isatty(2))
	// {
	// 	ft_putstr_fd("stdin, stdout or stderr have been changed\n", 2);
	// 	return (ENOTTY);
	// }
	hook_signals();
	g_status = 0;
	get_line(pipelines, env);
	rl_clear_history();
	printf("exit\n");
	return (g_status);
}

// WILDCARDS REDIRECTIONS
// CHECK REDIRECTIONS FILE