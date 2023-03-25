#include "minishell.h"

int	g_status;

char	***environnement(char **new_env)
{
	static char	**env = NULL;

	if (new_env)
		env = new_env;
	return (&env);
}

t_pipeline	*test(t_pipeline *pipelines)
{
	pipelines = malloc(sizeof(t_pipeline) * 2);
	pipelines->commands = malloc(sizeof(t_command) * 5);
	pipelines->commands->name = malloc(100);
	pipelines->commands->arguments = malloc(sizeof(char *) * 10);
	pipelines->commands->arguments[0] = malloc(100);
	pipelines->commands->arguments[1] = malloc(100);
	pipelines->commands->arguments[2] = malloc(100);
	pipelines->commands->arguments[3] = malloc(100);
	pipelines->commands[1].name = malloc(100);
	pipelines->commands[1].arguments = malloc(sizeof(char *) * 10);
	pipelines->commands[1].arguments[0] = malloc(100);
	pipelines->commands[1].arguments[1] = malloc(100);
	pipelines->commands[1].arguments[2] = malloc(100);
	pipelines->commands[2].name = malloc(100);
	pipelines->commands[2].arguments = malloc(sizeof(char *) * 10);
	pipelines->commands[2].arguments[0] = malloc(100);
	pipelines->commands[2].arguments[1] = malloc(100);
	pipelines->commands[2].arguments[2] = malloc(100);
	pipelines->commands[3].name = malloc(100);
	pipelines->commands[3].arguments = malloc(sizeof(char *) * 10);
	pipelines->commands[3].arguments[0] = malloc(100);
	pipelines->commands[3].arguments[1] = malloc(100);
	pipelines->commands[3].arguments[2] = malloc(100);
	pipelines->start_priority = NONE;
	pipelines->end_priority = NONE;
	pipelines->operator = NONE;
	pipelines->commands->name = "ls";
	pipelines->commands->arguments[0] = NULL;
	pipelines->commands->arguments[1] = NULL;
	pipelines->commands->arguments[2] = NULL;
	pipelines->commands->arguments[3] = NULL;
	pipelines->commands->input_file = 0;
	pipelines->commands->output_file = 1;
	pipelines->commands[1].name = "rev";
	pipelines->commands[1].arguments[0] = NULL;
	pipelines->commands[1].arguments[1] = NULL;
	pipelines->commands[1].arguments[2] = NULL;
	pipelines->commands[1].input_file = 0;
	pipelines->commands[1].output_file = 1;
	pipelines->commands[2].name = "sort";
	pipelines->commands[2].arguments[0] = NULL;
	pipelines->commands[2].arguments[1] = NULL;
	pipelines->commands[2].arguments[2] = NULL;
	pipelines->commands[2].input_file = 0;
	pipelines->commands[2].output_file = 1;
	pipelines->commands[3].name = "head";
	pipelines->commands[3].arguments[0] = "-3";
	pipelines->commands[3].arguments[1] = NULL;
	pipelines->commands[3].arguments[2] = NULL;
	pipelines->commands[3].input_file = 0;
	pipelines->commands[3].output_file = 1;
	pipelines->commands[4].name = NULL;
	pipelines[1].commands = NULL;
	return (pipelines);
}

int	get_line(t_pipeline *pipelines, char **env)
{
	char	*line;
	char	**new_env;

	line = readline(PROMPT);
	new_env = duplicate_bigarray(env);
	(void)environnement(new_env);
	while (line)
	{
		if (*line)
			add_history(line);
		//parse_line(pipelines, line);
		pipelines = test(pipelines);
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
