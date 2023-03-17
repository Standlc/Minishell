#include "minishell.h"

void	show_data(t_pipeline *pipelines)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	while (pipelines[i].commands)
	{
		printf("[\n");
		j = 0;
		while (pipelines[i].commands[j].name)
		{
			printf("\t{\n");
			printf("\t\tname: %s\n", pipelines[i].commands[j].name);
			k = 0;
			printf("\t\targuments: [");
			while (pipelines[i].commands[j].arguments && pipelines[i].commands[j].arguments[k])
			{
				printf("%s ", pipelines[i].commands[j].arguments[k]);
				k++;
			}
			printf("]\n");
			printf("\t\tinput: %s\n", pipelines[i].commands[j].input_file);
			printf("\t\touput: %s\n", pipelines[i].commands[j].output_file);
			printf("\t}\n");
			j++;
		}
		printf("\toperator: %d\n", pipelines[i].operator);
		printf("]\n");
		i++;
	}
}

int	get_line(t_pipeline *pipelines)
{
	char	*line;

	line = readline(PROMPT);
	while (line)
	{
		if (*line)
			add_history(line);
		pipelines = parse_line(line);
		if (pipelines)
		{
			show_data(pipelines);
			// free_pipelines(pipelines);
		}
		free(line);
		line = readline(PROMPT);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipeline	*pipelines;

	(void)argc;
	(void)argv;
	pipelines = NULL;
	// hook_signals();
	get_line(pipelines);
	printf("Exit\n");
	// rl_clear_history();
	return (0);
}
