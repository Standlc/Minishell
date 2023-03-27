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
				printf("%s ", pipelines[i].commands[j].arguments[k]);
				k++;
			}
			printf("]\n");
			printf("\t\tinput: %d\n", pipelines[i].commands[j].input_file);
			printf("\t\touput: %d\n", pipelines[i].commands[j].output_file);
			printf("\t\tis_end: %d\n", pipelines[i].commands[j].is_end);
			printf("\t\theredoc limit: %s\n", pipelines[i].commands[j].heredoc_limit);
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

// t_pipeline	*test(t_pipeline *pipelines)
// {
// 	pipelines = malloc(sizeof(t_pipeline) * 2);
// 	pipelines->commands = malloc(sizeof(t_command) * 5);
// 	pipelines->commands->arguments = malloc(sizeof(char *) * 10);
// 	pipelines->commands->arguments[0] = malloc(100);
// 	pipelines->commands->arguments[1] = malloc(100);
// 	pipelines->commands->arguments[2] = malloc(100);
// 	pipelines->commands->arguments[3] = malloc(100);
// 	pipelines->commands[1].arguments = malloc(sizeof(char *) * 10);
// 	pipelines->commands[1].arguments[0] = malloc(100);
// 	pipelines->commands[1].arguments[1] = malloc(100);
// 	pipelines->commands[1].arguments[2] = malloc(100);
// 	pipelines->commands[2].arguments = malloc(sizeof(char *) * 10);
// 	pipelines->commands[2].arguments[0] = malloc(100);
// 	pipelines->commands[2].arguments[1] = malloc(100);
// 	pipelines->commands[2].arguments[2] = malloc(100);
// 	pipelines->commands[3].arguments = malloc(sizeof(char *) * 10);
// 	pipelines->commands[3].arguments[0] = malloc(100);
// 	pipelines->commands[3].arguments[1] = malloc(100);
// 	pipelines->commands[3].arguments[2] = malloc(100);
// 	pipelines->parenthesis = 0;
// 	pipelines->operator = NONE;
// 	pipelines->commands->arguments[0] = "ls";
// 	pipelines->commands->arguments[1] = NULL;
// 	pipelines->commands->arguments[2] = NULL;
// 	pipelines->commands->arguments[3] = NULL;
// 	pipelines->commands->input_file = 0;
// 	pipelines->commands->output_file = 1;
// 	pipelines->commands->is_end = 1;
// 	pipelines->commands[1].arguments[0] = "rev";
// 	pipelines->commands[1].arguments[1] = NULL;
// 	pipelines->commands[1].arguments[2] = NULL;
// 	pipelines->commands[1].input_file = 0;
// 	pipelines->commands[1].output_file = 1;
// 	pipelines->commands[1].is_end = 1;
// 	pipelines->commands[2].arguments[0] = "sort";
// 	pipelines->commands[2].arguments[1] = NULL;
// 	pipelines->commands[2].arguments[2] = NULL;
// 	pipelines->commands[2].input_file = 0;
// 	pipelines->commands[2].output_file = 1;
// 	pipelines->commands[2].is_end = 1;
// 	pipelines->commands[3].arguments[0] = "head";
// 	pipelines->commands[3].arguments[1] = "-3";
// 	pipelines->commands[3].arguments[2] = NULL;
// 	pipelines->commands[3].input_file = 0;
// 	pipelines->commands[3].output_file = 1;
// 	pipelines->commands[3].is_end = 1;
// 	pipelines->commands[4].arguments = NULL;
// 	pipelines->commands[4].is_end = 0;
// 	pipelines[1].commands = NULL;
// 	return (pipelines);
// }

t_pipeline	*get_line(t_pipeline *pipelines, char **env)
{
	char	*line;
	char	**new_env;

	line = readline(PROMPT);
	new_env = duplicate_bigarray(env);
	if (g_status != 0)
		(free(line), exit(g_status));
	(void)environnement(new_env);
	while (line)
	{
		if (*line)
			add_history(line);
		pipelines = parse_line(line);
		if (pipelines)
		{
			show_data(pipelines);
			execution_global(pipelines);
			free_pipelines(pipelines);
		}
		free(line);
		line = readline(PROMPT);
	}
	return (pipelines);
}

int	main(int argc, char **argv, char **env)
{
	t_pipeline	*pipelines;

	(void)argc;
	(void)argv;
	pipelines = NULL;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_putstr_fd("stdin, stdout or stderr have been changed\n", 2);
		return (ENOTTY);
	}
	hook_signals();
	g_status = 0;
	pipelines = get_line(pipelines, env);
	rl_clear_history();
	printf("exit\n");
	return (0);
}

// WILDCARDS REDIRECTIONS
// CHECK REDIRECTIONS FILE