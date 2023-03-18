#include "minishell.h"

int	g_status;

char	***environnement(void)
{
	static char	**env;

	return (&env);
}

void	test(t_pipeline *pipelines)
{
	pipelines->start_priority = NONE;
	pipelines->end_priority = NONE;
	pipelines->operator = NONE;
	pipelines->commands->name = "echo";
	pipelines->commands->arguments[0] = "hello world";
	pipelines->commands->arguments[1] = NULL;
	pipelines->commands->input_file = NULL;
	pipelines->commands->output_file = NULL;
}

int	get_line(t_pipeline *pipelines, char **env)
{
	char	*line;
	char	**new_env;

	line = readline(PROMPT);
	new_env = *(environnement());
	new_env = duplicate_env(env);
	while (line)
	{
		if (*line)
			add_history(line);
		//parse_line(pipelines, line);
		test(pipelines);
		execution_global(pipelines);
		//free_pipelines(pipelines);
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
	//hook_signals();
	get_line(&pipelines, env);
	//printf("Exit\n");
	//rl_clear_history();
	return (0);
}
