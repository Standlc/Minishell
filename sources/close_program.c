#include "minishell.h"

void	free_pipelines(t_pipeline *pipelines)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;

	while (pipelines[i].commands)
	{
		j = 0;
		while (pipelines[i].commands[j].name)
		{
			free(pipelines[i].commands[j].name);
			k = 0;
			while (pipelines[i].commands[j].arguments && pipelines[i].commands[j].arguments[k])
			{
				free(pipelines[i].commands[j].arguments[k]);
				k++;
			}
			if (pipelines[i].commands[j].arguments)
				free(pipelines[i].commands[j].arguments);
			if (pipelines[i].commands[j].input_file > 2)
				close(pipelines[i].commands[j].input_file);
			if (pipelines[i].commands[j].output_file > 2)
				close(pipelines[i].commands[j].output_file);
			if (pipelines[i].commands[j].heredoc_limit)
				free(pipelines[i].commands[j].heredoc_limit);
			j++;
		}
		free(pipelines[i].commands);
		i++;
	}
	free(pipelines);
}