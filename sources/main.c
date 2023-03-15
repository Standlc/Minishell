#include "minishell.h"

void	show_data(t_pipeline *pipelines)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	printf("[\n");
	while (pipelines[i].commands)
	{
		printf("\t{\n");
		j = 0;
		while (pipelines[i].commands[j].name)
		{
			printf("\t\tname: %s\n", pipelines[i].commands[j].name);
			k = 0;
			printf("\t\targuments: [");
			while (pipelines[i].commands[j].arguments[k])
			{
				printf("%s ", pipelines[i].commands[j].arguments[k]);
				k++;
			}
			printf("]\n");
			j++;
		}
		printf("\t}\n");
		i++;
	}
	printf("]\n");
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
		show_data(pipelines);
		free_pipelines(pipelines);
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
	rl_clear_history();
	return (0);
}
