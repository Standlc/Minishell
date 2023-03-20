#include "minishell.h"

int	g_status;

char	***environnement(void)
{
	static char	**env;

	return (&env);
}

void	test(t_pipeline *pipelines)
{
	pipelines = malloc(sizeof(t_pipeline) * 2);
	pipelines->commands = malloc(sizeof(t_command) * 2);
	pipelines->commands->name = malloc(100);
	pipelines->commands->arguments = malloc(sizeof(char *) * 10);
	pipelines->commands->arguments[0] = malloc(100);
	pipelines->commands->arguments[1] = malloc(100);
	pipelines->commands->arguments[2] = malloc(100);
	pipelines->start_priority = NONE;
	pipelines->end_priority = NONE;
	pipelines->operator = NONE;
	pipelines->commands->name = "echo";
	pipelines->commands->arguments[0] = "-n";
	pipelines->commands->arguments[1] = "hello world";
	pipelines->commands->arguments[2] = NULL;
	pipelines->commands->input_file = 0;
	pipelines->commands->output_file = 1;
	pipelines->commands[1].name = NULL;
	pipelines[1].commands = NULL;
}

int	get_line(t_pipeline *pipelines, char **env)
{
	char	*line;
	char	**new_env;

	line = readline(PROMPT);
	new_env = *(environnement());
	new_env = duplicate_env(env);
	(void)new_env;
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
