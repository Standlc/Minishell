#include "minishell.h"

int	g_status;

int	get_line(t_pipeline *pipelines)
{
	char	*line;

	line = readline(PROMPT);
	while (line)
	{
		if (*line)
			add_history(line);
		parse_line(pipelines, line);
		execution(pipelines);
		free_pipelines(pipelines);
		free(line);
		line = readline(PROMPT);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	g_status = 0;
	hook_signals();
	get_line(&pipelines);
	printf("Exit\n");
	rl_clear_history();
	return (0);
}
