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
			while (pipelines[i].commands[j].arguments[k])
			{
				free(pipelines[i].commands[j].arguments[k]);
				k++;
			}
			j++;
		}
		free(pipelines[i].commands);
		i++;
	}
	free(pipelines);
}